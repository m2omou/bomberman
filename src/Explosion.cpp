#include "Explosion.hpp"
#include "ObjectMap.hpp"
#include "MyGame.hpp"
#include "WoodBox.hpp"
#include "Serializer.hpp"
#include "SteelBox.hpp"
#include <iostream>
#include <sstream>

Explosion::Explosion(MyGame *game, int x, int y,
		     int incx, int incy, int power, int ownerId)
  : Cube(x + 0.5f, 0.5f, y + 0.5f, 0.0f, 0.0f, 0.0f, 0.5f,
	 &game->getTexture().explosion)
{
  _game = game;
  _incx = incx;
  _incy = incy;
  _power = power;
  _timerClone = 0.01;
  _timerDestroy = 0.1;
  _boundaryBox = 0.25;
  _ownerId = ownerId;
}

bool		Explosion::applyEffect(APlayer &target, int, int) const
{
  t_casePlayer	&cur_case = _game->getPhysicalEngine().getCase(target);
  cur_case.content.remove(&target);
  if (dynamic_cast<Player1 *>(&target))
      _game->getPlayerMap()->setPlayer1(0);
  if (dynamic_cast<Player2 *>(&target))
      _game->getPlayerMap()->setPlayer2(0);
  if (dynamic_cast<APlayer *>(&target))
    {
      APlayer	*tmp;
      tmp = _game->getPlayerMap()->getPlayerById(_ownerId);
      if (dynamic_cast<Player1 *>(tmp))
	_game->getScoreManager().incScorePlayer1(5000);
      if (dynamic_cast<Player2 *>(tmp))
	_game->getScoreManager().incScorePlayer2(5000);
    }
  _game->getSound().playSound(DEATH);
  delete &target;
  return true;
}

std::string	Explosion::serialize() const
{
  std::stringstream	ss;
  std::string		tmp;

  tmp = Cube::serialize();
  ss << tmp.length() << " " << tmp << " " << _incx << " " << _incy << " "
     << _power << " " << _timerClone << " " << _timerDestroy << " " << _ownerId;
  return (ss.str());
}

void		Explosion::unserialize(const std::string &str)
{
  std::stringstream	ss(str);

  Cube::unserialize(Serializer::extractSerializable(ss));
  ss >> _incx;
  ss >> _incy;
  ss >> _power;
  ss >> _timerClone;
  ss >> _timerDestroy;
  ss >> _ownerId;
}

void		Explosion::update(void)
{
  _timerClone -= _game->getGameClock().getElapsedTime();
  _timerDestroy -= _game->getGameClock().getElapsedTime();
  if (_timerClone <= 0)
    {
      if (_incx || _incy)
	{
	  explode(_game, (int)_position.x + _incx, (int)_position.z + _incy,
		  _incx, _incy, _power - 1, _ownerId);
	}
    }
  if (_timerDestroy <= 0)
    {
      t_caseObject	&cur_case = _game->getObjectMap()->get((int)_position.x,
							       (int)_position.z);
      cur_case.content = 0;
    }
}

void		Explosion::explode(MyGame *game, int x, int y, int incx, int incy, int power,
				   int ownerId)
{
  t_caseObject	&cur_case = game->getObjectMap()->get(x, y);
  Explosion	*tmp;

  if (dynamic_cast<SteelBox *>(cur_case.content) == 0 &&
      dynamic_cast<WoodBox *>(cur_case.content) == 0 &&
      dynamic_cast<Bomb *>(cur_case.content) == 0 &&
      power)
    {
      tmp = new Explosion(dynamic_cast<MyGame *>(game), x, y, incx, incy, power, ownerId);
      tmp->initialize();
      cur_case.content = tmp;
    }
  if (dynamic_cast<WoodBox *>(cur_case.content) && power)
    {
      APlayer	*tmp;
      tmp = game->getPlayerMap()->getPlayerById(ownerId);
      if (dynamic_cast<Player1 *>(tmp))
	game->getScoreManager().incScorePlayer1(50);
      if (dynamic_cast<Player2 *>(tmp))
	game->getScoreManager().incScorePlayer2(50);
      delete (cur_case.content);
    }

  if (dynamic_cast<Bomb *>(cur_case.content))
    dynamic_cast<Bomb *>(cur_case.content)->setTimer(0);
}

int		Explosion::getOwnerId() const
{
  return _ownerId;
}

#include "PhysicalEngine.hpp"
#include "Vector3f.hpp"
#include "AObject.hpp"
#include "APlayer.hpp"
#include <math.h>
#include <stdio.h>

PhysicalEngine::PhysicalEngine(IPhysicalGame *game)
{
  _timeSpeed = 5000;
  _game = game;
}

bool		PhysicalEngine::detectCollision(AObject const &obj1,
						AObject const &obj2)
{
  if (obj1.getMaxX() < obj2.getMinX() ||
      obj1.getMinX() > obj2.getMaxX() ||
      obj1.getMaxZ() < obj2.getMinZ() ||
      obj1.getMinZ() > obj2.getMaxZ())
    return (false);
  return true;
}

void		PhysicalEngine::setMaps(ObjectMap *objectMap, PlayerMap *playerMap)
{
  _objectMap = objectMap;
  _playerMap = playerMap;
}

bool		PhysicalEngine::changeCase(Vector3f const &before, Vector3f const &after) const
{
  return ((int)before.x != (int)after.x ||
	  (int)before.y != (int)after.y ||
	  (int)before.z != (int)after.z);

}

t_caseObject	&PhysicalEngine::getCase(AObject &obj)
{
  return _objectMap->get((int)obj.getPos().x, (int)obj.getPos().z);
}

t_casePlayer	&PhysicalEngine::getCase(APlayer &obj)
{
  return _playerMap->get((int)obj.getPos().x, (int)obj.getPos().z);
}

bool		PhysicalEngine::update(APlayer &what)
{
  Vector3f	tmp;
  Vector3f	save;
  bool		ret;
  static const int	pos_table[][2] =
    {
      {-1,-1}, {-1, 0}, {-1, 1},
      {0,-1}, {0, 0}, {0, 1},
      {1,-1}, {1, 0}, {1, 1},
    };

  tmp = what.getPos();
  for (int i = 0; i < 8; i++)
    {
      t_caseObject	&cur_case = _objectMap->get((int)tmp.x + pos_table[i][0],
						    (int)tmp.z + pos_table[i][1]);
      if (cur_case.content && detectCollision(what, *cur_case.content))
	{
	  if (cur_case.content->applyEffect(what, pos_table[i][0], pos_table[i][1]))
	    return false;
	  if (cur_case.content->isBlocker())
	    block(what, pos_table[i][0], pos_table[i][1]);
	  ret = false;
	}
    }
  //On augmente la vitesse
  tmp = what.getSpeed();
  tmp = tmp + what.getAcc() * _timeSpeed * _game->getGameClock().getElapsedTime();
  //On simule les frottements
  tmp = tmp * 0.40;
  what.setSpeed(tmp);
  //Mise a jour de la rotation du personnage
  if (what.getAcc().x != 0 || what.getAcc().z != 0)
    what.setRot(0, atan2f(what.getAcc().x, what.getAcc().z) * 360 / (2 * M_PI), 0);
  //On test la ou le joueur va ce deplacer
  tmp = what.getPos() + what.getSpeed();
  save = what.getPos();
  if (changeCase(save, tmp))
    {
      t_casePlayer &cur_case = getCase(what);
      cur_case.content.remove(&what);
    }
  what.setPos(tmp);
  if (changeCase(save, tmp))
    {
      t_casePlayer &cur_case = getCase(what);
      cur_case.content.push_back(&what);
    }
  return ret;
}

float		PhysicalEngine::getTimeSpeed() const
{
  return _timeSpeed;
}

void		PhysicalEngine::setTimeSpeed(float const &timeSpeed)
{
  _timeSpeed = timeSpeed;
}

void		PhysicalEngine::block(APlayer &what, int x, int y)
{
  Vector3f		acc = what.getAcc();
  Vector3f		speed = what.getSpeed();

  speed.x = 0;
  speed.z = 0;
  acc.x += -x * what.getSpeedMax();
  acc.z += -y * what.getSpeedMax();
  what.setSpeed(speed);
  what.setAcc(acc);
}

std::string PhysicalEngine::serialize() const
{
  std::stringstream ss;

  ss << _timeSpeed;
  return ss.str();
}

void PhysicalEngine::unserialize(const std::string &str)
{
  std::stringstream ss(str);
  ss >> _timeSpeed;
}

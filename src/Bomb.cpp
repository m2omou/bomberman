#include "Serializer.hpp"
#include "Bomb.hpp"
#include "Cube.hpp"
#include "TextureBundle.hpp"
#include "Explosion.hpp"
#include "ObjectMap.hpp"
#include "IBombGame.hpp"
#include "MyGame.hpp"
#include "PhysicalEngine.hpp"

Bomb::Bomb(IBombGame *game,
	   float posx, float posy, float posz,
	   float rotx, float roty, float rotz,
	   float scale, int power, APlayer *owner)
{
  _game = game;
  _position.x = posx;
  _position.y = posy;
  _position.z = posz;
  _rotation.x = rotx;
  _rotation.y = roty;
  _rotation.z = rotz;
  _scale.x = scale;
  _scale.y = scale;
  _scale.z = scale;
  _power = power;
  if (owner)
    _ownerId = owner->getId();
  else
    _ownerId = -1;
  _timer = 3;
}

Bomb::Bomb(IBombGame *game,
	   float posx, float posy, float posz,
	   float rotx, float roty, float rotz,
	   float scalex, float scaley, float scalez, int power)
{
  _game = game;
  _position.x = posx;
  _position.y = posy;
  _position.z = posz;
  _rotation.x = rotx;
  _rotation.y = roty;
  _rotation.z = rotz;
  _scale.x = scalex;
  _scale.y = scaley;
  _scale.z = scalez;
  _power = power;
  _ownerId = -1;
  _timer = 3;
}

void	Bomb::initialize(void)
{
  _model = gdl::Model::load("ressources/assets/bomb.fbx");
}

void	Bomb::update()
{
  _timer -= _game->getGameClock().getElapsedTime();
  if (_timer <= 0)
    {
      t_caseObject	&cur_case = _game->getObjectMap()->get((int)_position.x,
							       (int)_position.z);
      cur_case.content = 0;
      Explosion::explode(dynamic_cast<MyGame *>(_game),
			 (int)_position.x, (int)_position.z, 0, 0, _power, _ownerId);
      Explosion::explode(dynamic_cast<MyGame *>(_game),
			 (int)_position.x + 1, (int)_position.z, 1, 0, _power, _ownerId);
      Explosion::explode(dynamic_cast<MyGame *>(_game),
			 (int)_position.x - 1, (int)_position.z, -1, 0, _power, _ownerId);
      Explosion::explode(dynamic_cast<MyGame *>(_game),
			 (int)_position.x, (int)_position.z + 1, 0, 1, _power, _ownerId);
      Explosion::explode(dynamic_cast<MyGame *>(_game),
			 (int)_position.x, (int)_position.z - 1, 0, -1, _power, _ownerId);
      if (_ownerId != -1)
	{
	  APlayer	*tmp = _game->getPlayerMap()->getPlayerById(_ownerId);
	  if (tmp)
	    tmp->addBomb();
	}

      _game->getSound().playSound(BOMB);
      delete (this);
    }
}

void		Bomb::setTimer(int timer)
{
  _timer = timer;
}

void	Bomb::draw(void)
{
  glPushMatrix(); //Sauvegrade de la matrice de transformation d'origine
  glTranslatef(_position.x, _position.y, _position.z);
  glRotatef(_rotation.x, 1, 0, 0);
  glRotatef(_rotation.y, 0, 1, 0);
  glRotatef(_rotation.z, 0, 0, 1);
  glScalef(1.0/400, 1.0/400, 1.0/400);
  _model.draw();
  glPopMatrix(); //Recuperation de la matrice de transformation d'origine.
}


std::string Bomb::serialize() const
{
  std::stringstream ss;
  std::string tmp;

  tmp = AObject::serialize();
  ss << tmp.length() << " " << tmp << " " << _power << " "
     << _ownerId << " " << _timer;
  return ss.str();
}

void Bomb::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  AObject::unserialize(Serializer::extractSerializable(ss));
  ss >> _power;
  ss >> _ownerId;
  ss >> _timer;
}

int Bomb::getPower() const
{
  return (_power);
}

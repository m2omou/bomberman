#include <sstream>
#include "AObject.hpp"
#include "APlayer.hpp"
#include "PhysicalEngine.hpp"
#include "Serializer.hpp"

AObject::AObject()
{
  _boundaryBox = 0.5;
  _bouncingCoef = 1.2;
}

const Vector3f	&AObject::getPos() const
{
  return (_position);
}

void	AObject::setPos(Vector3f const &position)
{
  _position = position;
}

void	AObject::setPos(float x, float y, float z)
{
  _position.x = x;
  _position.y = y;
  _position.z = z;
}

const Vector3f	&AObject::getRot() const
{
  return _rotation;
}

void	AObject::setRot(Vector3f const &rotation)
{
  _rotation = rotation;
}

void	AObject::setRot(float x, float y, float z)
{
  _rotation.x = x;
  _rotation.y = y;
  _rotation.z = z;
}

const Vector3f	&AObject::getScale() const
{
  return _scale;
}

void	AObject::setScale(Vector3f const &scale)
{
  _scale = scale;
}

void		AObject::setScale(float x, float y, float z)
{
  _scale.x = x;
  _scale.y = y;
  _scale.z = z;
}

const Vector3f	&AObject::getAcc() const
{
  return (_acceleration);
}

void		AObject::setAcc(Vector3f const &acceleration)
{
  _acceleration = acceleration;
}

void		AObject::setAcc(float x, float y, float z)
{
  _acceleration.x = x;
  _acceleration.y = y;
  _acceleration.z = z;
}

const Vector3f	&AObject::getSpeed() const
{
  return _speed;
}

void	AObject::setSpeed(Vector3f const &speed)
{
  _speed = speed;
}

void	AObject::setSpeed(float x, float y, float z)
{
  _speed.x = x;
  _speed.y = y;
  _speed.z = z;
}

float		AObject::getBoundaryBox() const
{
  return _boundaryBox;
}

void		AObject::setBoundaryBox(float const &boundaryBox)
{
  _boundaryBox = boundaryBox;
}

float		AObject::getBouncingCoef() const
{
  return _bouncingCoef;
}

void		AObject::setBouncingCoef(float const &bouncingCoef)
{
  _bouncingCoef = bouncingCoef;
}

float		AObject::getMaxX() const
{
  return _position.x + _boundaryBox;
}

float		AObject::getMaxZ() const
{
  return _position.z + _boundaryBox;
}

float		AObject::getMinX() const
{
  return _position.x - _boundaryBox;
}

float		AObject::getMinZ() const
{
  return _position.z - _boundaryBox;
}

bool		AObject::applyEffect(APlayer &target, int x, int y) const
{
  (void)target;
  (void)x;
  (void)y;
  return (false);
}

float		AObject::isBlocker() const
{
  return (true);
}

std::string AObject::serialize() const
{
  std::stringstream ss;
  std::string tmp;

  tmp = _acceleration.serialize();
  ss << tmp.length() << " " << tmp << " ";
  tmp = _speed.serialize();
  ss << tmp.length() << " " << tmp << " ";
  tmp = _position.serialize();
  ss << tmp.length() << " " << tmp << " ";
  tmp = _rotation.serialize();
  ss << tmp.length() << " " << tmp << " ";
  tmp = _scale.serialize();
  ss << tmp.length() << " " << tmp << " "
     << _boundaryBox << " " << _bouncingCoef;
  return ss.str();
}

void AObject::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  _acceleration.unserialize(Serializer::extractSerializable(ss));
  _speed.unserialize(Serializer::extractSerializable(ss));
  _position.unserialize(Serializer::extractSerializable(ss));
  _rotation.unserialize(Serializer::extractSerializable(ss));
  _scale.unserialize(Serializer::extractSerializable(ss));
  ss >> _boundaryBox >> _bouncingCoef;
}

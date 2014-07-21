#ifndef __AOBJECT_HPP__
# define __AOBJECT_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

#include "Input.hpp"
#include "GameClock.hpp"

#include "Vector3f.hpp"
#include "ISerializable.hpp"

class		APlayer;
class		MyGame;

class		AObject : public ISerializable
{
public:
  Vector3f		_acceleration;
  Vector3f		_speed;

  Vector3f		_position;
  Vector3f		_rotation;
  Vector3f		_scale;

  float			_boundaryBox;
  float			_bouncingCoef;

public:

  virtual void	initialize(void) = 0;
  virtual void	update() = 0;
  virtual void	draw(void) = 0;
  virtual ~AObject() {};

  AObject();
  virtual bool	applyEffect(APlayer &target, int x, int y) const;
  virtual float	isBlocker() const;

  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);

  const Vector3f	&getPos() const;
  void			setPos(Vector3f const &position);
  void			setPos(float x, float y, float z);
  const Vector3f	&getRot() const;
  void			setRot(Vector3f const &rotation);
  void			setRot(float x, float y, float z);
  const Vector3f	&getScale() const;
  void			setScale(Vector3f const &scale);
  void			setScale(float x, float y, float z);
  const Vector3f	&getAcc() const;
  void			setAcc(Vector3f const &acceleration);
  void			setAcc(float x, float y, float z);
  const Vector3f	&getSpeed() const;
  void			setSpeed(Vector3f const &speed);
  void			setSpeed(float x, float y, float z);
  float			getMaxSpeed() const;
  void			setMaxSpeed(float const &maxSpeed);
  float			getMaxAcc() const;
  void			setMaxAcc(float const &acceleration);
  float			getBoundaryBox() const;
  void			setBoundaryBox(float const &boundaryBox);
  float			getBouncingCoef() const;
  void			setBouncingCoef(float const &bouncingCoef);
  float			getMaxX() const;
  float			getMaxZ() const;
  float			getMinX() const;
  float			getMinZ() const;
};

#endif /* AOBJECT_HPP */

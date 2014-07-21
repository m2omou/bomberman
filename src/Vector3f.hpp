#ifndef __VECTOR3F_HPP__
# define __VECTOR3F_HPP__

#include "ISerializable.hpp"

struct Vector3f : public ISerializable
{
  float x;
  float y;
  float z;

  Vector3f(void);
  Vector3f(float x, float y, float z);

  float	getX() const;
  float getY() const;
  float getZ() const;
  bool	operator==(Vector3f const &vect) const;
  Vector3f operator+(Vector3f vect) const;
  Vector3f operator/(float coef) const;
  Vector3f operator*(float coef) const;

  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);

};

#endif /* VECTOR3F_HPP */

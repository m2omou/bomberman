#include "Vector3i.hpp"

Vector3i::Vector3i(void)
  : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3i::Vector3i(float x, float y, float z)
  : x(x), y(y), z(z)
{
}

float	Vector3i::getX() const
{
  return (x);
}

float	Vector3i::getY() const
{
  return (y);
}

float	Vector3i::getZ() const
{
  return (z);
}

bool	Vector3i::operator==(Vector3i const &vect) const
{
  return (x == vect.x && y == vect.y && z == vect.z);
}

Vector3i	Vector3i::operator+(Vector3i vect) const
{
  Vector3i	tmp;

  tmp.x = this->x + vect.x;
  tmp.y = this->y + vect.y;
  tmp.z = this->z + vect.z;
  return (tmp);
}

Vector3i	Vector3i::operator/(float coef) const
{
  Vector3i	(tmp);

  tmp.x = this->x / coef;
  tmp.y = this->y / coef;
  tmp.z = this->z / coef;
  return (tmp);
}

Vector3i	Vector3i::operator*(float coef) const
{
  Vector3i	tmp;

  tmp.x = this->x * coef;
  tmp.y = this->y * coef;
  tmp.z = this->z * coef;
  return tmp;
}

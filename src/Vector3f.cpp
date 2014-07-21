#include <sstream>
#include "Vector3f.hpp"

Vector3f::Vector3f(void)
  : x(0.0f), y(0.0f), z(0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
  : x(x), y(y), z(z)
{
}

float	Vector3f::getX() const
{
  return (x);
}

float	Vector3f::getY() const
{
  return (y);
}

float	Vector3f::getZ() const
{
  return (z);
}

bool	Vector3f::operator==(Vector3f const &vect) const
{
  return (x == vect.x && y == vect.y && z == vect.z);
}

Vector3f	Vector3f::operator+(Vector3f vect) const
{
  Vector3f	tmp;

  tmp.x = this->x + vect.x;
  tmp.y = this->y + vect.y;
  tmp.z = this->z + vect.z;
  return (tmp);
}

Vector3f	Vector3f::operator/(float coef) const
{
  Vector3f	(tmp);

  tmp.x = this->x / coef;
  tmp.y = this->y / coef;
  tmp.z = this->z / coef;
  return (tmp);
}

Vector3f	Vector3f::operator*(float coef) const
{
  Vector3f	tmp;

  tmp.x = this->x * coef;
  tmp.y = this->y * coef;
  tmp.z = this->z * coef;
  return tmp;
}

std::string Vector3f::serialize() const
{
  std::stringstream ss;

  ss << x << " " << y << " " << z;
  return ss.str();
}

void Vector3f::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  ss >> x >> y >> z;
}

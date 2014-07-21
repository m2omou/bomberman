#ifndef __VECTOR3I_HPP__
# define __VECTOR3I_HPP__

struct Vector3i
{
  float x;
  float y;
  float z;
  Vector3i(void);
  Vector3i(float x, float y, float z);

  float	getX() const;
  float getY() const;
  float getZ() const;
  bool	operator==(Vector3i const &vect) const;
  Vector3i operator+(Vector3i vect) const;
  Vector3i operator/(float coef) const;
  Vector3i operator*(float coef) const;
};

#endif /* VECTOR3I_HPP */

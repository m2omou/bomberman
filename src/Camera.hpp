#ifndef __CAMERA_HPP__
# define __CAMERA_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

#include "ICameraGame.hpp"
#include "GameClock.hpp"
#include "Input.hpp"
#include "Vector3f.hpp"
#include "AObject.hpp"
#include "ISerializable.hpp"

class Camera
  : public AObject
{
public:
  Camera(ICameraGame *game);
  void		initialize(void);
  virtual void	update() = 0;
  void		draw(void);
  virtual ~Camera(){};

protected:
  ICameraGame	*_game;
};

#endif /* CAMERA_HPP */

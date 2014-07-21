#ifndef __FREEFLYCAMERA_HPP__
# define __FREEFLYCAMERA_HPP__

#define		ROT_STEP	(M_PI / 360)
#define		MV_STEP		0.1
#define		isDown(x)	_game->getInput().isKeyDown(x)

#include <cmath>
#include "Camera.hpp"

class		FreeFlyCamera : public Camera
{
private:
  float		_speed;

public:
  FreeFlyCamera(ICameraGame *game);
  void		update();
  ~FreeFlyCamera();
};
#endif /* FREEFLYCAMERA_HPP */

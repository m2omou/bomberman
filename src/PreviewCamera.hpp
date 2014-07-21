#ifndef __PREVIEWCAMERA_HPP__
# define __PREVIEWCAMERA_HPP__

#include "Vector3f.hpp"
#include "Camera.hpp"
#include "APlayer.hpp"

class		PreviewCamera : public Camera
{
private:
  float		_zoom;

public:
  PreviewCamera(ICameraGame *game);
  void		update();
};

#endif /* PREVIEWCAMERA_HPP */

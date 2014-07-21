#include "Camera.hpp"

Camera::Camera(ICameraGame *game)
{
  _position.x = 0.0f;
  _position.y = 5.0f;
  _position.z = 0.0f;
  _rotation.x = -25.0f;
  _rotation.y = 45.0f;
  _rotation.z = 0.0f;
  _game = game;
}

void Camera::initialize(void)
{
  glEnable(GL_LIGHTING);

  //Try Anti Aliasing
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_POLYGON_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0f, 800.0f/600.0f, 1.0f, 10000.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void		Camera::draw(void)
{

}

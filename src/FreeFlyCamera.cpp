#include "FreeFlyCamera.hpp"
#include "MyGame.hpp"

FreeFlyCamera::FreeFlyCamera(ICameraGame *game)
  : Camera(game)
{
  _speed = 1000;
  _game->getWindow().setCursorAt(WIDTH / 2, HEIGHT / 2);
  _game->getWindow().showCursor(false);
}

void  FreeFlyCamera::update()
{
  Vector3f		tmp;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75.0f, (float)WIDTH/(float)HEIGHT, 1.0f, 100000.0f);
  usleep(1000000.0 / _speed);
  _rotation.y += ROT_STEP * (_game->getInput().getMousePositionX() - (WIDTH / 2));
  _rotation.x -= ROT_STEP * (_game->getInput().getMousePositionY() - (HEIGHT / 2));
  _game->getWindow().setCursorAt(WIDTH / 2, HEIGHT / 2);
  tmp.x = cosf(_rotation.y + M_PI_2);
  tmp.z = sinf(_rotation.y + M_PI_2);
  if (isDown(gdl::Keys::D))
    {
      _position.x += tmp.x * MV_STEP;
      _position.z += tmp.z * MV_STEP;
    }
  if (isDown(gdl::Keys::A))
    {
      _position.x -= tmp.x * MV_STEP;
      _position.z -= tmp.z * MV_STEP;
    }
  tmp.x = cosf(_rotation.x) * cosf(_rotation.y);
  tmp.y = sinf(_rotation.x);
  tmp.z = cosf(_rotation.x) * sinf(_rotation.y);
  if (isDown(gdl::Keys::W))
    {
      _position.x += tmp.x * MV_STEP;
      _position.y += tmp.y * MV_STEP;
      _position.z += tmp.z * MV_STEP;
    }
  if (isDown(gdl::Keys::S))
    {
      _position.x -= tmp.x * MV_STEP;
      _position.y -= tmp.y * MV_STEP;
      _position.z -= tmp.z * MV_STEP;
    }
  if (_game->getInput().isKeyDown(gdl::Keys::Add))
    _speed++;
  if (_game->getInput().isKeyDown(gdl::Keys::Subtract))
    _speed--;
  tmp.x = cosf(_rotation.x) * cosf(_rotation.y);
  tmp.y = sinf(_rotation.x);
  tmp.z = cosf(_rotation.x) * sinf(_rotation.y);
  gluLookAt(_position.x, _position.y, _position.z,
	    tmp.x + _position.x, tmp.y + _position.y, tmp.z + _position.z,
	    0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
}

FreeFlyCamera::~FreeFlyCamera()
{
  _game->getWindow().showCursor(true);
}

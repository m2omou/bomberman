#include "PreviewCamera.hpp"
#include "MyGame.hpp"

PreviewCamera::PreviewCamera(ICameraGame *game)
  : Camera(game)
{
  _zoom = 0;
}

void  PreviewCamera::update()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (_game->getInput().isKeyDown(gdl::Keys::Left))
      _zoom+= M_PI * 42 * _game->getGameClock().getElapsedTime();
  if (_game->getInput().isKeyDown(gdl::Keys::Right))
    _zoom-= M_PI * 42 * _game->getGameClock().getElapsedTime();
  gluPerspective(75.0f, (float)WIDTH/(float)HEIGHT, 1.0f, 100000.0f);
  gluLookAt(0,
	    MAX(_game->getObjectMap()->height(),
		_game->getObjectMap()->width()) * 0.95,
	    MAX(_game->getObjectMap()->height(),
		_game->getObjectMap()->width()) * 0.95,
	    -MAX(_game->getObjectMap()->height(),
		 _game->getObjectMap()->width()) * 0.40,
	    0, 0,
	    0.0f, 1.0f, 0.0f);
  glRotated(_zoom, 0, 1, 0);
  glTranslated(-_game->getObjectMap()->width() / 2,
  	       0,
  	       -_game->getObjectMap()->height() / 2);
  glMatrixMode(GL_MODELVIEW);
}

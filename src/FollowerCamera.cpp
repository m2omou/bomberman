#include "FollowerCamera.hpp"
#include "MyGame.hpp"

FollowerCamera::FollowerCamera(ICameraGame *game, PlayerMap const *players)
  : Camera(game)
{
  _players = players;
  _zoom = 4;
}

void  FollowerCamera::update()
{
  if (_players->getPlayer1() && _players->getPlayer2())
    updateTwoPlayer();
  else if (_players->getPlayer1())
    updateOnePlayer(_players->getPlayer1());
  else if (_players->getPlayer2())
    updateOnePlayer(_players->getPlayer2());
}

void		FollowerCamera::updateOnePlayer(APlayer const *player)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (_game->getInput().isKeyDown(gdl::Keys::Numpad9))
    _zoom+=0.1;
  if (_game->getInput().isKeyDown(gdl::Keys::Numpad3))
    _zoom-=0.1;
  gluPerspective(75.0f, (float)WIDTH/(float)HEIGHT, 1.0f, 100000.0f);
  gluLookAt(player->getPos().x,
	    player->getPos().y + _zoom * _zoom / 4,
	    player->getPos().z + _zoom,
  	    player->getPos().x,
	    player->getPos().y + 0.5,
	    player->getPos().z,
   	    0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
}

void		FollowerCamera::updateTwoPlayer()
{
  Vector3f	pos;

  pos.x = _players->getPlayer1()->getPos().x - _players->getPlayer2()->getPos().x;
  pos.y = _players->getPlayer1()->getPos().y - _players->getPlayer2()->getPos().y;
  pos.z = _players->getPlayer1()->getPos().z - _players->getPlayer2()->getPos().z;
  pos.z *= 1.5;
  float	dist = MAX(fabs(pos.z), fabs(pos.x));
  dist = MAX(dist, 3);
  pos.x = (_players->getPlayer1()->getPos().x + _players->getPlayer2()->getPos().x) / 2;
  pos.y = (_players->getPlayer1()->getPos().y + _players->getPlayer2()->getPos().y) / 2;
  pos.z = (_players->getPlayer1()->getPos().z + _players->getPlayer2()->getPos().z) / 2;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(90, (float)WIDTH/(float)HEIGHT, 1.0f, 100000.0f);
  gluLookAt(pos.x,
	    pos.y + dist * 0.5 + 2,
	    pos.z + dist * 0.2 + 3,
	    pos.x,
	    pos.y,
	    pos.z,
   	    0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
}

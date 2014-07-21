#ifndef __FOLLOWERCAMERA_HPP__
# define __FOLLOWERCAMERA_HPP__

#include "Vector3f.hpp"
#include "Camera.hpp"
#include "APlayer.hpp"

class		PlayerMap;

class		FollowerCamera : public Camera
{
private:
  PlayerMap const	*_players;
  float		_zoom;

public:
  FollowerCamera(ICameraGame *game, PlayerMap const *players);
  void		update();
  void		updateOnePlayer(APlayer const * player);
  void		updateTwoPlayer();
};

#endif /* FOLLOWERCAMERA_HPP */

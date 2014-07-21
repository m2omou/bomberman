#ifndef __SPEEDBONUS_HPP__
# define __SPEEDBONUS_HPP__

#include "Cube.hpp"
#include "IBonus.hpp"

class		MyGame;

class		SpeedBonus : public Cube, public IBonus
{
private:
  MyGame	*_game;
public:
  SpeedBonus(float posx, float posy, float posz,
	     float rotx, float roty, float rotz,
	     float scale, MyGame *game);
  static AObject	*create(int x, int y, MyGame *game);
  bool		applyEffect(APlayer &target, int x, int y) const;
};

#endif /* SPEEDBONUS_HPP */

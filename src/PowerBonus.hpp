#ifndef __POWERBONUS_HPP__
# define __POWERBONUS_HPP__

#include "Cube.hpp"
#include "IBonus.hpp"

class		MyGame;

class		PowerBonus : public Cube, public IBonus
{
private:
  MyGame	*_game;
public:
  PowerBonus(float posx, float posy, float posz,
	     float rotx, float roty, float rotz,
	     float scale, MyGame *game);
  static AObject	*create(int x, int y, MyGame *game);
  bool			applyEffect(APlayer &target, int x, int y) const;
};

#endif /* POWERBONUS_HPP */

#ifndef __INVENTORYBONUS_HPP__
# define __INVENTORYBONUS_HPP__

#include "Cube.hpp"
#include "IBonus.hpp"
#include "IBonus.hpp"

class		MyGame;

class		InventoryBonus : public Cube, public IBonus
{
private:
  MyGame	*_game;
public:
  InventoryBonus(float posx, float posy, float posz,
	     float rotx, float roty, float rotz,
	     float scale, MyGame *game);
  static AObject	*create(int x, int y, MyGame *game);
  bool		applyEffect(APlayer &target, int x, int y) const;
};

#endif /* INVENTORYBONUS_HPP */

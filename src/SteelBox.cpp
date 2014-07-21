#include "SteelBox.hpp"
#include "MyGame.hpp"

AObject		*SteelBox::create(int x, int y, MyGame *game)
{
  return new SteelBox(x + 0.5, 0.5, y + 0.5, 0, 0, 0, 0.5, game);
}

SteelBox::SteelBox(float posx, float posy, float posz,
		 float rotx, float roty, float rotz,
		 float scale, MyGame *game)
  : Cube(posx, posy, posz, rotx, roty, rotz, scale, &game->getTexture().steelBox)
{

}

#include "WoodBox.hpp"
#include "MyGame.hpp"
#include "SteelBox.hpp"
#include "PowerBonus.hpp"
#include "InventoryBonus.hpp"
#include "SpeedBonus.hpp"

typedef	AObject *(*fct)(int, int, MyGame *game);

static const fct bonusList[] = {
  &InventoryBonus::create,
  &PowerBonus::create,
  &SpeedBonus::create
};

AObject		*WoodBox::create(int x, int y, MyGame *game)
{
  return new WoodBox(x + 0.5, 0.5, y + 0.5, 0, 0, 0, 0.5, game);
}

WoodBox::WoodBox(float posx, float posy, float posz,
		 float rotx, float roty, float rotz,
		 float scale, MyGame *game)
  : Cube(posx, posy, posz, rotx, roty, rotz, scale, &game->getTexture().woodBox)
{
  _game = game;
}

WoodBox::~WoodBox()
{
  t_caseObject	&cur_case = _game->getObjectMap()->get((int)_position.x,
						       (int)_position.z);
  int			i = rand() % 6;

  _game->getSound().playSound(BOX);
  if (i < 3)
    cur_case.content = (bonusList[i])((int)_position.x, (int)_position.z, _game);
  else
    cur_case.content = 0;
}

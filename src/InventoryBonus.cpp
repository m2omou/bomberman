#include "InventoryBonus.hpp"
#include "MyGame.hpp"

AObject		*InventoryBonus::create(int x, int y, MyGame *game)
{
  return new InventoryBonus(x + 0.5, 0.5, y + 0.5, 0, 0, 0, 0.3, game);
}

InventoryBonus::InventoryBonus(float posx, float posy, float posz,
		 float rotx, float roty, float rotz,
		 float scale, MyGame *game)
  : Cube(posx, posy, posz, rotx, roty, rotz, scale, &game->getTexture().trollFace)
{
  _game = game;
}

bool		InventoryBonus::applyEffect(APlayer &target, int , int ) const
{
  t_caseObject	&cur_case = _game->getObjectMap()->get((int)_position.x,
  						       (int)_position.z);
  APlayer	*tmp;

  _game->getSound().playSound(BOMB_BONUS);
  tmp = dynamic_cast<APlayer *>(&target);
  if (tmp != 0)
    tmp->addBomb();
  cur_case.content = 0;
  if (dynamic_cast<Player1 *>(&target))
    _game->getScoreManager().incScorePlayer1(50);
  else if (dynamic_cast<Player2 *>(&target))
    _game->getScoreManager().incScorePlayer2(50);
  delete this;
  return true;
}

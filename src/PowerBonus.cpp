#include "PowerBonus.hpp"
#include "MyGame.hpp"

AObject		*PowerBonus::create(int x, int y, MyGame *game)
{
  return new PowerBonus(x + 0.5, 0.5, y + 0.5, 0, 0, 0, 0.3, game);
}

PowerBonus::PowerBonus(float posx, float posy, float posz,
		       float rotx, float roty, float rotz,
		       float scale, MyGame *game)
  : Cube(posx, posy, posz, rotx, roty, rotz, scale, &game->getTexture().danger)
{
  _game = game;
}

bool		PowerBonus::applyEffect(APlayer &target, int , int ) const
{
  t_caseObject	&cur_case = _game->getObjectMap()->get((int)_position.x,
  						       (int)_position.z);
  APlayer	*tmp;

  _game->getSound().playSound(POWER_BONUS);
  tmp = dynamic_cast<APlayer *>(&target);
  if (tmp != 0)
    tmp->bombPowerUp();
  if (dynamic_cast<Player1 *>(&target))
    _game->getScoreManager().incScorePlayer1(50);
  else if (dynamic_cast<Player2 *>(&target))
    _game->getScoreManager().incScorePlayer2(50);
  cur_case.content = 0;
  delete this;
  return true;
}

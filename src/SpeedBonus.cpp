#include "SpeedBonus.hpp"
#include "MyGame.hpp"

AObject		*SpeedBonus::create(int x, int y, MyGame *game)
{
  return new SpeedBonus(x + 0.5, 0.5, y + 0.5, 0, 0, 0, 0.3, game);
}

SpeedBonus::SpeedBonus(float posx, float posy, float posz,
		       float rotx, float roty, float rotz,
		       float scale, MyGame *game)
  : Cube(posx, posy, posz, rotx, roty, rotz, scale, &game->getTexture().life)
{
  _game = game;
}

bool		SpeedBonus::applyEffect(APlayer &target, int , int ) const
{
  t_caseObject	&cur_case = _game->getObjectMap()->get((int)_position.x,
  						       (int)_position.z);
  _game->getSound().playSound(SPEED_BONUS);
  target.increaseSpeedMax();
  if (dynamic_cast<Player1 *>(&target))
    _game->getScoreManager().incScorePlayer1(50);
  else if (dynamic_cast<Player2 *>(&target))
    _game->getScoreManager().incScorePlayer2(50);
  cur_case.content = 0;
  delete this;
  return true;
}

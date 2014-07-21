#include "RealPlayer.hpp"
#include "MyGame.hpp"
#include "IPlayerGame.hpp"

RealPlayer::RealPlayer(IPlayerGame *game, int x, int y)
  : APlayer(game, x, y)
{
}

void		RealPlayer::update()
{
  APlayer::update();
  setAcc(0, 0, 0);
  for (int i = 0; getBinding()[i].value != 0; i++)
    {
      if (_game->getInput().isKeyDown(getBinding()[i].key))
	(this->*(getBinding()[i].value))();
    }
  move();
}

//PLAYER1
const RealPlayer::t_map Player1::_binding[] = {
  {gdl::Keys::Right,	&APlayer::moveRight},
  {gdl::Keys::Left,	&APlayer::moveLeft},
  {gdl::Keys::Up,	&APlayer::moveUp},
  {gdl::Keys::Down,	&APlayer::moveDown},
  // {gdl::Keys::Add,	&APlayer::increaseSpeedMax},
  // {gdl::Keys::Subtract,&APlayer::discreaseSpeedMax},
  {gdl::Keys::Numpad0,	&APlayer::plantBomb},
  {gdl::Keys::Escape, 0}
};

Player1::Player1(IPlayerGame *game, int x, int y)
  : RealPlayer(game, x, y)
{
}

const RealPlayer::t_map		*Player1::getBinding() const
{
  return _binding;
}

APlayer		*createPlayer1(int x, int y, MyGame *game)
{
  return new Player1(game, x, y);
}

//PLAYER 2
const RealPlayer::t_map Player2::_binding[] = {
  {gdl::Keys::D,	&APlayer::moveRight},
  {gdl::Keys::A,	&APlayer::moveLeft},
  {gdl::Keys::W,	&APlayer::moveUp},
  {gdl::Keys::S,	&APlayer::moveDown},
  {gdl::Keys::Space,	&APlayer::plantBomb},
  {gdl::Keys::Escape, 0}
};

Player2::Player2(IPlayerGame *game, int x, int y)
  : RealPlayer(game, x, y)
{
}

const RealPlayer::t_map		*Player2::getBinding() const
{
  return _binding;
}

APlayer		*createPlayer2(int x, int y, MyGame *game)
{
  return new Player2(game, x, y);
}

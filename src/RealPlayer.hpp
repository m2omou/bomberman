#ifndef __REALPLAYER_HPP__
# define __REALPLAYER_HPP__

#include <iostream>
#include <typeinfo>
#include "APlayer.hpp"
#include "FreeFlyCamera.hpp"

class		MyGame;
class		IPlayerGame;

class		RealPlayer : public APlayer
{
protected:
  typedef struct	s_map
  {
    gdl::Keys::Key	key;
    void		(APlayer::*value)();
  }			t_map;

public:
  RealPlayer(IPlayerGame *game, int x, int y);
  void				update();
  virtual const t_map		*getBinding() const = 0;
};


class		Player1 : public RealPlayer
{
  static const t_map	_binding[];
public:
  Player1(IPlayerGame *game, int x, int y);
  const t_map		*getBinding() const;
};

APlayer		*createPlayer1(int x, int y, MyGame *game);

class		Player2 : public RealPlayer
{
  static const t_map	_binding[];
public:
  Player2(IPlayerGame *game, int x, int y);
  const t_map		*getBinding() const;
};

APlayer		*createPlayer2(int x, int y, MyGame *game);

#endif /* REALPLAYER_HPP */

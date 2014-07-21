#ifndef __BOMB_HPP__
# define __BOMB_HPP__

#include "Model.hpp"
#include "AObject.hpp"

class		IBombGame;

class		Bomb : public AObject
{
private:
  gdl::Model	_model;
  IBombGame	*_game;
  int		_power;
  int		_ownerId;
  float		_timer;

public:
  Bomb(IBombGame *game,
       float posx, float posy, float posz,
       float rotx, float roty, float rotz,
       float scale, int power, APlayer *owner = 0);
  Bomb(IBombGame *game,
       float posx, float posy, float posz,
       float rotx, float roty, float rotz,
       float scalex, float scaley, float scalez, int power);
  void	initialize(void);
  void	update();
  void	draw(void);
  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
  void	setTimer(int timer);
  int	getPower() const;
};

#endif /* BOMB_HPP */

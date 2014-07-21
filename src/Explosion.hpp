#ifndef __EXPLOSION_HPP__
# define __EXPLOSION_HPP__

#include "Cube.hpp"

class		MyGame;

class		Explosion : public Cube
{
  MyGame	*_game;
  int		_incx;
  int		_incy;
  int		_power;
  float		_timerClone;
  float		_timerDestroy;
  int		_ownerId;

public:
  Explosion(MyGame *game,
	    int x, int y,
	    int incx, int incy, int power, int ownerId);
  bool		applyEffect(APlayer &target, int x, int y) const;
  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
  void		update(void);
  static void		explode(MyGame *game, int x, int y, int incx, int incy, int power,
				int ownerId);
  int		getOwnerId() const;
};

#endif /* EXPLOSION_HPP */

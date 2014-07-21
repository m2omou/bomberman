#ifndef __IPHYSICALGAME_HPP__
# define __IPHYSICALGAME_HPP__

#include <vector>
#include "GameClock.hpp"

class		APlayer;

class		IPhysicalGame
{
public:
  virtual int				getNbIaPlayer() const = 0;
  virtual int				getNbRealPlayer() const = 0;
  virtual int				getNbPlayer() const = 0;
  virtual gdl::GameClock		&getGameClock() = 0;
  virtual ~IPhysicalGame() {};
};

#endif /* IPHYSICALGAME_HPP */

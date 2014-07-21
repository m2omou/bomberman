#ifndef __IBOMBGAME_HPP__
# define __IBOMBGAME_HPP__

#include <vector>
#include <list>
#include "ObjectMap.hpp"

class	Bomb;
class	PhysicalEngine;
class	TextureBundle;
class	APlayer;
class	GameClock;
class	InputSafe;
class	PlayerMap;
class	Sound;

class		IBombGame
{
public:
  virtual int			getNbIaPlayer() const = 0;
  virtual int			getNbRealPlayer() const = 0;
  virtual int			getNbPlayer() const = 0;
  virtual PhysicalEngine	&getPhysicalEngine() = 0;
  virtual gdl::GameClock	&getGameClock() = 0;
  virtual gdl::Input		&getInput() = 0;
  virtual TextureBundle		&getTexture() = 0;
  virtual ObjectMap		*getObjectMap() = 0;
  virtual PlayerMap		*getPlayerMap() = 0;
  virtual Sound			&getSound() const = 0;
  virtual ~IBombGame() {};
};

#endif /* IBOMBGAME_HPP */

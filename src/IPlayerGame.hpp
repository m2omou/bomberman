#ifndef __IPLAYERGAME_HPP__
# define __IPLAYERGAME_HPP__

#include <vector>
#include "Map.hpp"
#include "APlayer.hpp"
#include "PhysicalEngine.hpp"
#include "Camera.hpp"

class		PhysicalEngine;
class		APlayer;
class		ThreadPool;

class		IPlayerGame
{
public:
  virtual int			getNbIaPlayer() const = 0;
  virtual int			getNbRealPlayer() const = 0;
  virtual int			getNbPlayer() const = 0;
  virtual PhysicalEngine	&getPhysicalEngine() = 0;
  virtual gdl::GameClock	&getGameClock() = 0;
  virtual gdl::Input		&getInput() = 0;
  virtual Camera const		&getCamera() const = 0;
  virtual ObjectMap		*getObjectMap() = 0;
  virtual ObjectMap const	*getObjectMap() const = 0;

  virtual ~IPlayerGame(){};
};

#endif /* IPLAYERGAME_HPP */

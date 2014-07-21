#ifndef __ICAMERAGAME_HPP__
# define __ICAMERAGAME_HPP__

#include "Input.hpp"
#include "ObjectMap.hpp"
#include "ISerializable.hpp"
#include "GameClock.hpp"

class		ICameraGame
{
public:
  virtual ~ICameraGame() {};
  virtual gdl::Input		&getInput() = 0;
  virtual gdl::Window		&getWindow() = 0;
  virtual gdl::Window const	&getWindow() const = 0;
  virtual ObjectMap			*getObjectMap() = 0;
  virtual ObjectMap const		*getObjectMap() const = 0;
  virtual gdl::GameClock		&getGameClock() = 0;
};

#endif /* ICAMERAGAME_HPP */

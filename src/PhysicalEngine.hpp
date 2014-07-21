#ifndef __PHYSICALENGINE_HPP__
# define __PHYSICALENGINE_HPP__

#include <map>
#include "IPhysicalGame.hpp"
#include "AObject.hpp"
#include "ObjectMap.hpp"
#include "PlayerMap.hpp"

#define	MAX(x, y) ((x > y) ? (x) : (y))
#define	MIN(x, y) ((x < y) ? (x) : (y))

class		PhysicalEngine : public ISerializable
{
private:
  ObjectMap	*_objectMap;
  PlayerMap	*_playerMap;
  float		_timeSpeed;
  IPhysicalGame	*_game;

private: //Funcion
  static bool		detectCollision(AObject const &obj1, AObject const &obj2);
  bool		changeCase(Vector3f const &before, Vector3f const &after) const;

public:
  PhysicalEngine(IPhysicalGame *game);
  void		setMaps(ObjectMap *objectMap, PlayerMap *playerMap);
  bool		update(APlayer &what);
  float		getTimeSpeed() const;
  void		setTimeSpeed(float const &timeSpeed);

  virtual std::string	serialize() const;
  virtual void		unserialize(const std::string &);

  t_caseObject	&getCase(AObject &obj);
  t_casePlayer	&getCase(APlayer &obj);
  void		block(APlayer &what, int x, int y);
};

#endif /* PHYSICALENGINE_HPP */

#ifndef __SERIALIZABLE_FACTORY_HPP__
#define __SERIALIZABLE_FACTORY_HPP__

#include <map>
#include "ISerializable.hpp"
#include "MyGame.hpp"

class SerializableFactory
{
private:

  static MyGame *_game;

  SerializableFactory();
  static std::map<std::string,
		  ISerializable *(*)(int, int, MyGame *)> _constructors;

  static ISerializable *createBomb(int, int, MyGame *);
  static ISerializable *createExplosion(int, int, MyGame *);
  static ISerializable *createObjectMap(int, int, MyGame *);
  static ISerializable *createPlayerMap(int, int, MyGame *);
  static ISerializable *createSquare(int, int, MyGame *);
public:

  static void init();

  static void registerMyGame(MyGame *);

  static ISerializable *create(const std::string &);
};

#endif

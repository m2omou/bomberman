#include <typeinfo>
#include "SerializableFactory.hpp"

#include "Bomb.hpp"
#include "Explosion.hpp"
#include "IAPlayer.hpp"
#include "InventoryBonus.hpp"
#include "ObjectMap.hpp"
#include "PlayerMap.hpp"
#include "PowerBonus.hpp"
#include "RealPlayer.hpp"
#include "Square.hpp"
#include "SteelBox.hpp"
#include "WoodBox.hpp"
#include "SpeedBonus.hpp"

std::map<std::string, ISerializable *(*)(int, int, MyGame *)> SerializableFactory::_constructors;
MyGame *SerializableFactory::_game = 0;

ISerializable *SerializableFactory::create(const std::string &str)
{
  std::map<std::string, ISerializable *(*)(int, int, MyGame *)>::iterator it
    = _constructors.find(str);

  if (it != _constructors.end())
    return it->second(0, 0, _game);
  else
    return 0;
}

void SerializableFactory::init()
{
  _constructors[typeid(Bomb).name()] = SerializableFactory::createBomb;
  _constructors[typeid(Explosion).name()] = SerializableFactory::createExplosion;
  _constructors[typeid(IAPlayer).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>
    (createIAPlayer);
  _constructors[typeid(InventoryBonus).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>
    (InventoryBonus::create);
  _constructors[typeid(ObjectMap).name()] = SerializableFactory::createObjectMap;
  _constructors[typeid(PlayerMap).name()] = SerializableFactory::createPlayerMap;
  _constructors[typeid(PowerBonus).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>(PowerBonus::create);
  _constructors[typeid(Player1).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>(createPlayer1);
  _constructors[typeid(Player2).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>(createPlayer2);
  _constructors[typeid(Square).name()] = SerializableFactory::createSquare;
  _constructors[typeid(SteelBox).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>(SteelBox::create);
  _constructors[typeid(WoodBox).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>(WoodBox::create);
  _constructors[typeid(SpeedBonus).name()]
    = reinterpret_cast<ISerializable *(*)(int, int, MyGame *)>(SpeedBonus::create);
}

void SerializableFactory::registerMyGame(MyGame *game)
{
  _game = game;
}

ISerializable *SerializableFactory::createBomb(int, int, MyGame *game)
{
  return new Bomb(game, 0, 0, 0, 0, 0, 0, 0, 0);
}

ISerializable *SerializableFactory::createExplosion(int, int, MyGame *game)
{
  return new Explosion(game, 0, 0, 0, 0, 0, 0);
}

ISerializable *SerializableFactory::createObjectMap(int, int, MyGame *)
{
  return new ObjectMap(0, 0);
}

ISerializable *SerializableFactory::createPlayerMap(int, int, MyGame *)
{
  return new PlayerMap(0, 0);
}

ISerializable *SerializableFactory::createSquare(int, int, MyGame *)
{
  return new Square;
}

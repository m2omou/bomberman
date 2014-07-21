#include <math.h>

#include "IAPlayer.hpp"
#include "IPlayerGame.hpp"
#include "MyGame.hpp"

IAPlayer::IAPlayer(IPlayerGame *game, int x, int y)
  : APlayer(game, x, y)
{
  srand(time(0));
  _dir.x = x;
  _dir.y = 0;
  _dir.z = y;
}

void		IAPlayer::initLua(SLB::Manager *m)
{
  static bool	isInit = false;

  if (!isInit)
    {
      isInit = true;
      SLB::Class< s_caseObject, SLB::Instance::NoCopyNoDestroy >("s_caseObject", m)
	.set("getContent", &t_caseObject::getContent);
      SLB::Class< Vector3f >("Vector3f", m)
	.set("getZ", &Vector3f::getZ)
	.set("getX", &Vector3f::getX)
	.set("getY", &Vector3f::getY);
      SLB::Class< IPlayerGame, SLB::Instance::NoCopyNoDestroy >("IPlayerGame", m)
      	.set("getObjectMap", (ObjectMap*(IPlayerGame::*)())&IPlayerGame::getObjectMap);
      SLB::Class< Map<t_caseObject>, SLB::Instance::NoCopyNoDestroy >("Map", m)
	.set("width", &Map<t_caseObject>::width)
	.set("height", &Map<t_caseObject>::height)
	.set("get", &Map<t_caseObject>::get);
      SLB::Class< ObjectMap, SLB::Instance::NoCopyNoDestroy >("ObjectMap", m)
	.inherits<Map<t_caseObject> >();
      SLB::Class< AObject, SLB::Instance::NoCopyNoDestroy >("AObject", m);
      SLB::Class< APlayer, SLB::Instance::NoCopyNoDestroy >("APlayer", m)
	.inherits<AObject>();
      SLB::Class< IAPlayer, SLB::Instance::NoCopyNoDestroy >("IAPlayer", m)
	.constructor<IPlayerGame *, int, int>()
	.set("moveDown", &APlayer::moveDown)
	.set("moveUp", &APlayer::moveUp)
	.set("moveRight", &APlayer::moveRight)
	.set("moveLeft", &APlayer::moveLeft)
	.set("move", &APlayer::move)
	.set("getGame", &APlayer::getGame)
	.set("update", &APlayer::update)
	.set("getPos", &AObject::getPos)
	.set("setNewDir", &IAPlayer::setNewDir)
	.set("getDir", &IAPlayer::getDir)
	.set("isDirReached", &IAPlayer::isDirReached)
	.set("plantBomb", &APlayer::plantBomb)
	.set("getNbBomb", &APlayer::getNbBomb)
	.inherits<APlayer>()
	.inherits<AObject>();
    }
}

void		IAPlayer::update(void)
{
  LuaManager	lua(&IAPlayer::initLua);
  LuaManager::MyScript s("src/script");

  APlayer::update();
  setAcc(0, 0, 0);
  s.call(this, "IA");
}

bool			IAPlayer::isSafe(int x, int y)
{
  int			i;

  for (i = 0; (i + x) < _game->getObjectMap()->width(); ++i)
    if (dynamic_cast<Bomb *>(_game->getObjectMap()->get(i + x, y).content) &&
	dynamic_cast<Bomb *>(_game->getObjectMap()->
			     get(i + x, y).content)->getPower() >= i)
      return (false);
  for (i = 0; (i + x) >= 0; --i)
    if (dynamic_cast<Bomb *>(_game->getObjectMap()->get(i + x, y).content) &&
	dynamic_cast<Bomb *>(_game->getObjectMap()->
			     get(i + x, y).content)->getPower() >= -i)
      return (false);
  for (i = 0; (i + y) >= 0; --i)
    if (dynamic_cast<Bomb *>(_game->getObjectMap()->get(x, y + i).content) &&
	dynamic_cast<Bomb *>(_game->getObjectMap()->
			     get(x, y + i).content)->getPower() >= -i)
      return (false);
  for (i = 0; (i + y) < _game->getObjectMap()->height(); ++i)
    if (dynamic_cast<Bomb *>(_game->getObjectMap()->get(x, y + i).content) &&
	dynamic_cast<Bomb *>(_game->getObjectMap()->
			     get(x, y + i).content)->getPower() >= i)
      return (false);
  return (true);
}

bool			IAPlayer::testCase(int x, int y, int mode)
{
  if (_game->getObjectMap()->get(x, y).content)
    return (false);
  if (mode)
    return (isSafe(x, y));
  return (true);
}

void			IAPlayer::setNewDir()
{
  static int		first = 1;
  std::deque<Vector3f>	list;
  std::deque<Vector3f>	list2;
  Vector3f		neighbor(_position.x + 1, 1, _position.z);

  if (first)
    {
      first = 0;
      srand48(time(NULL));
    }
  _old_dir = _dir;
  if (_old_dir.y != 2 && neighbor.x < getGame()->getObjectMap()->width())
    {
      if (testCase(neighbor.x, neighbor.z, 1))
	list.push_front(neighbor);
      if (testCase(neighbor.x, neighbor.z, 0))
	list2.push_front(neighbor);
    }
  neighbor.x = _position.x - 1;
  neighbor.y = 2;
  if (_old_dir.y != 1 && neighbor.x >= 0)
    {
      if (testCase(neighbor.x, neighbor.z, 1))
	list.push_front(neighbor);
      if (testCase(neighbor.x, neighbor.z, 0))
	list2.push_front(neighbor);
    }
  neighbor.x = _position.x;
  neighbor.z = _position.z + 1;
  neighbor.y = 3;
  if (_old_dir.y != 4 && neighbor.z < _game->getObjectMap()->height())
    {
      if (testCase(neighbor.x, neighbor.z, 1))
	list.push_front(neighbor);
      if (testCase(neighbor.x, neighbor.z, 0))
	list2.push_front(neighbor);
    }
  neighbor.z = _position.z - 1;
  neighbor.y = 4;
  if (_old_dir.y != 3 && neighbor.z >= 0)
    {
      if (testCase(neighbor.x, neighbor.z, 1))
	list.push_front(neighbor);
      if (testCase(neighbor.x, neighbor.z, 0))
	list2.push_front(neighbor);
    }
  if (!list.empty())
    _dir = list[lrand48() % list.size()];
  else if (!testCase(_position.x, _position.z, 1) && !list2.empty())
    _dir = list2[lrand48() % list2.size()];
  else
    _dir.y = 0;
}

bool			IAPlayer::isDirReached()
{
  return (floor(_dir.x) == floor(_position.x) &&
	  floor(_dir.z) == floor(_position.z));
}

int			IAPlayer::getDir()
{
  return (_dir.y);
}

APlayer		*createIAPlayer(int x, int y, MyGame *game)
{
  return new IAPlayer(game, x, y);
}

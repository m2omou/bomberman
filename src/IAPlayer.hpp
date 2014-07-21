#ifndef __IAPLAYER_HPP__
# define __IAPLAYER_HPP__

#include <cstdlib>
#include <iostream>

#include "LuaManager.hpp"
#include "APlayer.hpp"

class		MyGame;

class		IAPlayer : public APlayer
{
public:
  IAPlayer(IPlayerGame *game, int x, int y);
  void			update(void);

  /* functions that prepare lua */
  static void		initLua(SLB::Manager *);

  /* action-functions to use with lua */
  void			setNewDir();
  int			getDir();
  bool			isDirReached();
  bool			testCase(int, int, int);
  bool			isSafe(int, int);

private:
  Vector3f	_dir;
  Vector3f	_old_dir;
};

APlayer		*createIAPlayer(int x, int y, MyGame *game);

#endif /* IAPLAYER_HPP */

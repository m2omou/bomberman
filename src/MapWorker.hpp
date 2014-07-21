#ifndef __MAPWORKER_HPP__
# define __MAPWORKER_HPP__

#include                <iostream>
#include                <string>
#include		<vector>
#include                <map>
#include		<stdexcept>

class		MyGame;
class		AObject;
class		APlayer;
class		PlayerMap;
class		ObjectMap;
class		LoadMap;

typedef	AObject *(*fct)(int, int, MyGame *game);
typedef	APlayer *(*fct_player)(int, int, MyGame *game);

class			MapWorker
{
public:
  enum		case_type
    {
      SPACE = '.',
      STEELBOX = 'x',
      WOODBOX = 'w'
    };

public:
  static ObjectMap	*createObjectMap(MyGame *game, LoadMap &asciiMap);
  static PlayerMap	*createPlayerMap(MyGame *game, LoadMap &asciiMap, bool multi);
  static ObjectMap	*createObjectMapAleat(MyGame *game, int width, int height,
					      int nb_player);
  static PlayerMap	*createPlayerMapAleat(MyGame *game, bool multi, int width, int height,
					      int nb_player, ObjectMap *);
};

#endif /* MAPWORKER_HPP */

#include	<fstream>
#include	"MapWorker.hpp"
#include	"Cube.hpp"
#include	"IAPlayer.hpp"
#include	"RealPlayer.hpp"
#include	"LoadMap.hpp"
#include	"MyGame.hpp"
#include	"ObjectMap.hpp"
#include	"PlayerMap.hpp"
#include	"WoodBox.hpp"
#include	"SteelBox.hpp"

ObjectMap		*MapWorker::createObjectMap(MyGame *game, LoadMap &asciiMap)
{
  char		c;
  ObjectMap	*map;

  std::map<char, fct>	image;
  image[STEELBOX] = SteelBox::create;
  image[WOODBOX] = WoodBox::create;

  map = new ObjectMap(asciiMap.width, asciiMap.height);
  for (unsigned int x = 0; x < asciiMap.width; x++)
    {
      for (unsigned int y = 0; y < asciiMap.height; y++)
	{
	  c = asciiMap.data[y][x];
	  if (!(image.find(c) == image.end() || c == SPACE))
	    map->get(x, y).content = image[c](x, y, game);
	  else
	    map->get(x, y).content = 0;
	}
    }
  return (map);
}

PlayerMap		*MapWorker::createPlayerMap(MyGame *game, LoadMap &asciiMap, bool multi)
{
  char		c;
  PlayerMap	*map;

  std::map<char, fct_player>	image;
  image['1'] = createPlayer1;
  if (multi)
    image['2'] = createPlayer2;
  else
    image['2'] = createIAPlayer;
  image['I'] = createIAPlayer;

  map = new PlayerMap(asciiMap.width, asciiMap.height);
  for (unsigned int x = 0; x < asciiMap.width; x++)
    {
      for (unsigned int y = 0; y < asciiMap.height; y++)
	{
	  APlayer	*tmp = 0;

	  c = asciiMap.data[y][x];
	  if (!(image.find(c) == image.end() || c == '.'))
	    {
	      tmp = image[c](x, y, game);
	      map->get(x, y).content.push_back(tmp);
	    }
	  if (c == '1')
	    {
	      if (map->getPlayer1() == 0)
		map->setPlayer1(tmp);
	      else
		throw std::runtime_error("Several 'Player One' on map");
	    }
	  if (c == '2' && multi)
	    {
	      if (map->getPlayer2() == 0)
		map->setPlayer2(tmp);
	      else
		throw std::runtime_error("Several 'Player Two' on map");
	    }
	}
    }
  return (map);
}

ObjectMap	*MapWorker::createObjectMapAleat(MyGame *game, int width, int height,
						 int)
{
  ObjectMap		*map;

  map = new ObjectMap(width, height);
  for (int x = 0; x < width; x++)
    {
      for (int y = 0; y < height; y++)
	{
	  if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
	    map->get(x, y).content = SteelBox::create(x, y, game);
	  else if (x % 2 == 0 && y % 2 == 0)
	    map->get(x, y).content = SteelBox::create(x, y, game);
	  else if ((x % 2 && !(y % 2)) || (!(x % 2) && y % 2))
	    map->get(x, y).content = WoodBox::create(x, y, game);
	  else
	    map->get(x, y).content = 0;
	}
    }
  return map;
}

PlayerMap	*MapWorker::createPlayerMapAleat(MyGame *game, bool multi, int width, int height,
						 int nb_player, ObjectMap *_objMap)
{
  PlayerMap		*map;
  int			height_case =  (height - 2 + (height & 1)) / 2;
  int			width_case = (width - 2 + (width & 1)) / 2;

  if (nb_player > height_case * width_case || width < 3 || height < 3)
    return (0);
  int incx = width_case / (int) (sqrt(nb_player) + 0.5);
  int incy = height_case / (int) (sqrt(nb_player) + 0.5);
  map = new PlayerMap(width, height);
  int		i = 0;
  for (int x = 0; x < width_case; x += incx)
    {
      for (int y = 0; y < width_case; y += incy)
	{
	  if (i < nb_player)
	    {
	      int realx = x * 2 + 1;
	      int realy = y * 2 + 1;
	      if (i == 0)
		{
		  map->setPlayer1(createPlayer1(realx, realy, game));
		  map->get(realx, realy).content.push_back(map->getPlayer1());
		}
	      else if (i == 1 && multi)
		{
		  map->setPlayer2(createPlayer2(realx, realy, game));
		  map->get(realx, realy).content.push_back(map->getPlayer2());
		}
	      else
		map->get(realx, realy).content.push_back(createIAPlayer(realx, realy, game));
	      if (realx + 1 != width - 1)
		_objMap->get(realx + 1 , realy).content = 0;
	      if (realx - 1 != 0)
		_objMap->get(realx - 1 , realy).content = 0;
	      if (realy + 1 != height - 1)
		_objMap->get(realx, realy + 1).content = 0;
	      if (realy - 1 != 0)
		_objMap->get(realx, realy - 1).content = 0;
	    }
	  i++;
	}
    }
  return (map);
}

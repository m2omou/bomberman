#ifndef __MYGAME_HPP__
# define __MYGAME_HPP__

#include <typeinfo>
#include <cstdlib>
#include <list>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Color.hpp"
#include "ScoreManager.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "FreeFlyCamera.hpp"
#include "FollowerCamera.hpp"
#include "AObject.hpp"
#include "RealPlayer.hpp"
#include "IAPlayer.hpp"
#include "Input.hpp"
#include "Square.hpp"
#include "Cube.hpp"
#include "Image.hpp"
#include "TextureBundle.hpp"
#include "LoadMap.hpp"
#include "Bomb.hpp"

#include "Sound.hpp"

#include "IBombGame.hpp"
#include "IPhysicalGame.hpp"
#include "IPlayerGame.hpp"
#include "Menu.hpp"

#define		WIDTH		1300
#define		HEIGHT		700
#define		SC_TO_USC(x) ((x) * 1000000.0)

class		ObjectMap;
class		PlayerMap;

class MyGame : public gdl::Game,
	       public IPlayerGame,
	       public IPhysicalGame,
	       public ICameraGame,
	       public IBombGame,
	       public ISerializable
{
protected:
  //General Game Settings
  int				_nbIaPlayer;
  int				_nbRealPlayer;
  std::string			_mapFilename;

  //General Game Data
  PhysicalEngine		_physicalEngine;
  ObjectMap			*_objectMap;
  PlayerMap			*_playerMap;
  ScoreManager			_scoreManager;
  int				_counter;

  //Graphic engine
  Camera			*_camera;
  TextureBundle			_textureBundle;
  float				_fps;
  Square			_floor;

  //Menu
  Menu				_menu;
  bool				_lockGame;
  int				_button;
  LoadMap			_asciiMap;

  Sound				*_sound;

private://Functions
  void				switchCamera();
  void				limitFps();

public:
  MyGame();
  ~MyGame();
  void				initialize(void);
  void				update(void);
  void				draw(void);
  void				unload(void);
  void				save(const std::string &file);
  void				load(const std::string &file);
  int				getNbIaPlayer() const;
  int				getNbRealPlayer() const;
  int				getNbPlayer() const;
  PhysicalEngine		&getPhysicalEngine();
  PhysicalEngine const		&getPhysicalEngine() const;
  gdl::GameClock		&getGameClock();
  gdl::GameClock const		&getGameClock() const;
  Camera			&getCamera();
  Camera const			&getCamera() const;
  gdl::Input			&getInput();
  gdl::Input const		&getInput() const;
  gdl::Window			&getWindow();
  gdl::Window const		&getWindow() const;
  TextureBundle   		&getTexture();
  TextureBundle	const		&getTexture() const;
  ObjectMap			*getObjectMap();
  ObjectMap const		*getObjectMap() const;
  PlayerMap			*getPlayerMap();
  PlayerMap const		*getPlayerMap() const;
  Square			&getFloor();
  Square const			&getFloor() const;
  Sound				&getSound() const;
  bool				getLockGame() const;
  ScoreManager			&getScoreManager();
  void				resetCounter();

public:
  void				setAsciiMap(LoadMap &);

  //Serialization
  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);

  void				setCamera(Camera *);
  void				setFps(float);
  void				setObjectMap(ObjectMap *map);
  void				setPlayerMap(PlayerMap *map);
  void				setLockGame(bool lock);
};

#endif /* MYGAME_HPP */

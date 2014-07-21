#include <sstream>
#include "MyGame.hpp"
#include "ObjectMap.hpp"
#include "PlayerMap.hpp"
#include "LoadMap.hpp"
#include "MapWorker.hpp"
#include "Menu.hpp"
#include "Text.hpp"
#include "Serializer.hpp"

MyGame::MyGame()
  : Game(),
    _physicalEngine(this),
    _floor(0,0,0, 90,0,0, 500, &_textureBundle.grass)
{
  _counter = 3;
  _lockGame = 1;
  _camera = new FreeFlyCamera(this);
  _sound = new Sound();
  _button = 0;
  _playerMap = 0;
  _objectMap = 0;
}

void MyGame::unload(void)
{
  delete _playerMap;
  delete _objectMap;
  delete _camera;
}

MyGame::~MyGame()
{
}

void MyGame::initialize(void)
{
  window_.setWidth(WIDTH);
  window_.setHeight(HEIGHT);
  window_.setTitle("My Bomberman !");
  window_.create();
  gdl::Model::load("ressources/assets/bomb.fbx");
  _camera->initialize();
  _menu.run_intro(*this, window_);
}

void MyGame::switchCamera()
{
 if (input_.isKeyDown(gdl::Keys::Num1) && typeid(*_camera) != typeid(FreeFlyCamera))
    {
      delete _camera;
      _camera = new FreeFlyCamera(this);
    }
 else if (input_.isKeyDown(gdl::Keys::Num2) && typeid(*_camera) != typeid(FollowerCamera))
    {
      delete _camera;
      _camera = new FollowerCamera(this, _playerMap);
    }
}

void	MyGame::limitFps()
{
  static float		lastTime;
  float			elaspedTime;

  elaspedTime = gameClock_.getTotalGameTime() - lastTime;
  if (1 / _fps > elaspedTime)
    usleep(SC_TO_USC(1 / _fps - elaspedTime));
  elaspedTime = gameClock_.getTotalGameTime() - lastTime;
  lastTime = gameClock_.getTotalGameTime();
}

void MyGame::update(void)
{
  std::list<Bomb*>::iterator	it;

  limitFps();
  FMOD_System_Update(getSound().getSystem());
  if (input_.isKeyDown(gdl::Keys::Escape) && _lockGame != 1)
    {
      _lockGame = 1;
      _menu.set_button(Menu::Pause);
    }
  if (_lockGame != 1)
    {
      switchCamera();
      _camera->update();
      _objectMap->update();
      if (!_counter)
	_playerMap->update();
      _floor.update();
      if (_playerMap->gameEnd() ||
	  (!_playerMap->getPlayer1() && !_playerMap->getPlayer2()))
	{
	  _lockGame = true;
	  if (_playerMap->getPlayer1() != 0)
	    _menu.set_button(Menu::YouWin);
	  else
	    _menu.set_button(Menu::GameOver);
	}
    }
}

void MyGame::draw(void)
{
  if (_lockGame != 1)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glClearColor(0.74f, 0.84f, 95.0f, 1.0f);	//Couleur de background
      glClearDepth(1.0f);	//Remise a zero des test de profondeur
      _camera->draw();
      _objectMap->draw();
      _playerMap->draw();
      _floor.draw();
      _scoreManager.draw();
      if (_counter)
	{
	  gdl::Text		text_name;
	  std::stringstream	str;

	  str << _counter;
	  text_name.setFont("ressources/ttf/Simpsonfont.ttf");
	  text_name.setText(str.str());
	  text_name.setSize(100);
	  text_name.setPosition(WIDTH / 2, HEIGHT / 2);
	  text_name.draw();
	}
      window_.display();
      if (_counter)
	{
	  sleep(1);
	  gameClock_.update();
	  --_counter;
	}
    }
  else
    {
      usleep(100);
      _camera->initialize();
      _menu.display_menu(input_, *this);
    }
}

int				MyGame::getNbIaPlayer() const
{
  return _nbIaPlayer;
}

int				MyGame::getNbRealPlayer() const
{
  return _nbRealPlayer;
}

int				MyGame::getNbPlayer() const
{
  return _nbIaPlayer + _nbRealPlayer;
}

PhysicalEngine			&MyGame::getPhysicalEngine()
{
  return _physicalEngine;
}

PhysicalEngine const		&MyGame::getPhysicalEngine() const
{
  return _physicalEngine;
}

gdl::GameClock			&MyGame::getGameClock()
{
  return gameClock_;
}

gdl::GameClock const		&MyGame::getGameClock() const
{
  return gameClock_;
}

gdl::Input			&MyGame::getInput()
{
  return input_;
}

gdl::Input const		&MyGame::getInput() const
{
  return input_;
}

Camera				&MyGame::getCamera()
{
  return *_camera;
}

Camera const			&MyGame::getCamera() const
{
  return *_camera;
}

TextureBundle  			&MyGame::getTexture()
{
  return _textureBundle;
}

TextureBundle const	       	&MyGame::getTexture() const
{
  return _textureBundle;
}

gdl::Window			&MyGame::getWindow()
{
    return window_;
}

gdl::Window const		&MyGame::getWindow() const
{

  return window_;
}

ObjectMap			*MyGame::getObjectMap()
{
  return _objectMap;
}

ObjectMap const			*MyGame::getObjectMap() const
{
  return _objectMap;
}

PlayerMap			*MyGame::getPlayerMap()
{
  return _playerMap;
}

PlayerMap const			*MyGame::getPlayerMap() const
{
  return _playerMap;
}

Square				&MyGame::getFloor()
{
  return _floor;
}

Square const			&MyGame::getFloor() const
{
  return _floor;
}

Sound				&MyGame::getSound() const
{
  return *_sound;
}

bool				MyGame::getLockGame() const
{
  return _lockGame;
}

void				MyGame::setAsciiMap(LoadMap &map)
{
  _asciiMap = map;
}

void				MyGame::setCamera(Camera *cam)
{
  _camera = cam;
}

void				MyGame::setFps(float fps)
{
  _fps = fps;
}

void				MyGame::setObjectMap(ObjectMap *map)
{
  _objectMap = map;
}

void				MyGame::setPlayerMap(PlayerMap *map)
{
  _playerMap = map;
}

void				MyGame::setLockGame(bool lock)
{
  _lockGame = lock;
}

std::string MyGame::serialize() const
{
  std::stringstream ss;

  ss << _nbIaPlayer << " " << _nbRealPlayer << " " << _mapFilename;
  return ss.str();
}

void MyGame::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  ss >> _nbIaPlayer >> _nbRealPlayer >> _mapFilename;
}

void				MyGame::save(const std::string &file)
{
  Serializer			s;

  s << this << &_physicalEngine << _objectMap << _playerMap << &_scoreManager;
  s.pack(file);
}

void				MyGame::load(const std::string &file)
{
  Serializer			s;

  s.unpack(file);
  this->unserialize(s.getNextSerializableString(s.id<MyGame>()));
  _physicalEngine.unserialize(s.getNextSerializableString(s.id<PhysicalEngine>()));
  _objectMap = static_cast<ObjectMap*>(s.getNextSerializable(s.id<ObjectMap>()));
  _playerMap = static_cast<PlayerMap*>(s.getNextSerializable(s.id<PlayerMap>()));
  _scoreManager.unserialize(s.getNextSerializableString(s.id<ScoreManager>()));
  _physicalEngine.setMaps(_objectMap, _playerMap);
}

ScoreManager			&MyGame::getScoreManager()
{
  return _scoreManager;
}

void				MyGame::resetCounter()
{
  _counter = 3;
}

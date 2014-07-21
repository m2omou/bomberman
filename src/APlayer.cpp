#include <sstream>
#include <cstdlib>

#include "APlayer.hpp"
#include "IPlayerGame.hpp"
#include "MyGame.hpp"
#include "Serializer.hpp"

int	APlayer::count = 0;

APlayer::APlayer(IPlayerGame *game, int x, int y)
{
  _boundaryBox = 0.3;
  setPos(x + 0.5f, 0.0f, y + 0.5f);
  setRot(0.0f, 0.0f, 0.0f);
  setAcc(0.0f, 0.0f, 0.0f);
  setSpeed(0.0f, 0.0f, 0.0f);
  _game = game;
  id = count++;
  _bombPower = 2;
  _bombInventory = 1;
  _speedMax = 0.001;
}

void		APlayer::initialize()
{
  gdl::Color		color(rand() % 255 , rand() % 255, rand() % 255);

  _model = gdl::Model::load("ressources/assets/marvin.fbx");
  _model.set_default_model_color(color);
  gdl::Model::cut_animation(_model, "Take 001", 0, 35, "Start");
  gdl::Model::cut_animation(_model, "Take 001", 35, 54, "Run");
  gdl::Model::cut_animation(_model, "Take 001", 54, 120, "Stop");
  gdl::Model::cut_animation(_model, "Take 001", 0, 0, "Reset");
}

void		APlayer::stopAllAnimation()
{
  _model.stop_animation("Start");
  _model.stop_animation("Run");
  _model.stop_animation("Stop");
  _model.stop_animation("Reset");
}

void		APlayer::runIfNotRunning(std::string const &name,
					 gdl::Anim::AnimStates state)
{
  if (!_model.animation_hasStarted(name))
    {
      stopAllAnimation();
      _model.play(name, state);
    }
}

void		APlayer::update()
{
  if (IS_ZERO(_speed.x) && IS_ZERO(_speed.y) && IS_ZERO(_speed.z))
    runIfNotRunning("Reset", gdl::Anim::RUN);
  else
    runIfNotRunning("Run", gdl::Anim::LOOP);
  _model.update(_game->getGameClock());
}

void		APlayer::draw(void)
{
  glPushMatrix();//Sauvegrade de la matrice de transformation d'origine
  glTranslatef(_position.x, _position.y, _position.z);
  glRotatef(_rotation.y, 0, 1, 0);
  glScalef(1.0/300, 1.0/300, 1.0/300);
  _model.draw();
  glPopMatrix();//Recuperation de la matrice de transformation d'origine.
}

void			APlayer::moveUp()
{
  _acceleration.z += -_speedMax;
}

void			APlayer::moveDown()
{
  _acceleration.z += _speedMax;
}

void			APlayer::moveRight()
{
  _acceleration.x += _speedMax;
}

void			APlayer::moveLeft()
{
  _acceleration.x += -_speedMax;
}

void			APlayer::timeSpeedUp()
{
  PhysicalEngine &tmp = _game->getPhysicalEngine();
  tmp.setTimeSpeed(tmp.getTimeSpeed() + 42);
}

void			APlayer::timeSpeedDown()
{
  PhysicalEngine &tmp = _game->getPhysicalEngine();
  tmp.setTimeSpeed(tmp.getTimeSpeed() - 42);
}

IPlayerGame		*APlayer::getGame()
{
  return _game;
}

bool			APlayer::move()
{
  return _game->getPhysicalEngine().update(*this);
}

void			APlayer::plantBomb()
{
  t_caseObject  &cur_case = _game->getObjectMap()->get((int)_position.x, (int)_position.z);
  Bomb                          *tmp;

  if (cur_case.content == 0 && _bombInventory)
    {
      _bombInventory--;
      tmp = new Bomb(dynamic_cast<IBombGame *>(_game),
		     (int)_position.x + 0.5,
		     0.5,
		     (int)_position.z + 0.5, 0, 0, 0, 1, _bombPower, this);
      tmp->initialize();
      cur_case.content = tmp;
    }
}

void			APlayer::bombPowerUp()
{
  _bombPower++;
}

void			APlayer::addBomb()
{
  _bombInventory++;
}

int			APlayer::getId() const
{
  return id;
}

float			APlayer::getSpeedMax() const
{
  return _speedMax;
}

void			APlayer::increaseSpeedMax()
{
  if (_speedMax < 1.6)
    _speedMax *= 1.1;
}

void			APlayer::discreaseSpeedMax()
{
  _speedMax /= 1.1;
}

APlayer::~APlayer()
{
}

std::string APlayer::serialize() const
{
  std::stringstream ss;
  std::string tmp;

  tmp = AObject::serialize();
  ss << tmp.length() << " " << tmp << " ";
  ss << count << " " << id << " " << _bombPower << " " << _bombInventory;
  return (ss.str());
}

void APlayer::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  AObject::unserialize(Serializer::extractSerializable(ss));
  ss >> count >> id >> _bombPower >> _bombInventory;
}

int    APlayer::getNbBomb() const
{
  return (_bombInventory);
}

#ifndef __APLAYER_HPP__
# define __APLAYER_HPP__

#include <string>

#include "AObject.hpp"
#include "Model.hpp"
#include "Clock.hpp"
#include "Bomb.hpp"
#include "Color.hpp"

#define		COEF_ANIM_SPEED		(1.0 / 600.0)
#define		PRES		0.00001
#define		IS_ZERO(x)	((x) < PRES && (x) > -PRES)

class		IPlayerGame;

class		APlayer : public AObject
{
protected:
  static int		count;
  int			id;
  gdl::Model		_model;
  IPlayerGame		*_game;
  int			_bombPower;
  int			_bombInventory;
  float			_speedMax;

private: //Function
  void			stopAllAnimation();
  void			runIfNotRunning(std::string const &name,
					gdl::Anim::AnimStates state = gdl::Anim::LOOP);

public:
  APlayer(IPlayerGame *game, int x, int y);
  virtual ~APlayer();

  void			initialize(void);
  void			update();
  void			draw(void);
  void			moveUp();
  void			moveDown();
  void			moveRight();
  IPlayerGame		*getGame();
  void			moveLeft();
  void			timeSpeedUp();
  void			timeSpeedDown();
  void			plantBomb();
  void			bombPowerUp();
  bool			move();
  void			addBomb();
  float			getSpeedMax()const;
  void			increaseSpeedMax();
  void			discreaseSpeedMax();
  int			getNbBomb() const;

  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
  int			getId() const;
};

#endif /* APLAYER_HPP */

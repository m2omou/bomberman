#ifndef __PLAYERMAP_HPP__
#define __PLAYERMAP_HPP__

#include <list>
#include "Map.hpp"
#include "ISerializable.hpp"

class		APlayer;

typedef	struct		s_casePlayer : public ISerializable
{
  std::list<APlayer *>	content;
  int		x;
  int		y;
  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
}			t_casePlayer;

class		PlayerMap
  : public Map<t_casePlayer>
{
  APlayer	*_player1;
  APlayer	*_player2;

public:
  PlayerMap(int width, int height);
  void	initialize(void);
  void	update(void);
  void	draw(void);
  void	setPlayer1(APlayer *player1);
  void	setPlayer2(APlayer *player2);
  APlayer	*getPlayer1();
  APlayer	*getPlayer2();
  APlayer const	*getPlayer1() const;
  APlayer const	*getPlayer2() const;
  APlayer	*getPlayerById(int id);
  void	dump() const;
  bool	gameEnd() const;
  virtual ~PlayerMap();

  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
};

#endif /* PLAYERMAP_HPP */

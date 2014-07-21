#include <typeinfo>
#include <list>
#include "PlayerMap.hpp"
#include "RealPlayer.hpp"
#include "APlayer.hpp"
#include "SerializableFactory.hpp"

PlayerMap::PlayerMap(int width, int height)
  : Map(width, height)
{
  _player1 = 0;
  _player2 = 0;
}

void	PlayerMap::initialize(void)
{
  PlayerMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content.empty() == false)
	{
	  for (std::list<APlayer *>::iterator it2 = (*it).content.begin();
	       it2 != (*it).content.end();
	       ++it2)
	    (*it2)->initialize();
	}
    }
}

void	PlayerMap::update()
{
  PlayerMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content.empty() == false)
	{
	  for (std::list<APlayer *>::iterator it2 = (*it).content.begin();
	       it2 != (*it).content.end();
	       )
	    {
	      APlayer	*tmp = *it2;
	      it2++;
	      tmp->update();
	    }
	}
    }
}

void	PlayerMap::draw(void)
{
  PlayerMap::iterator	it;

  int		i = 0;
  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content.empty() == false)
	{
	  for (std::list<APlayer *>::iterator it2 = (*it).content.begin();
	       it2 != (*it).content.end();
	       ++it2)
	    (*it2)->draw();
	}
      i++;
    }
}

void	PlayerMap::dump() const
{
  PlayerMap::const_iterator	it;

  int		i = 0;
  for (it = this->begin(); it != this->end(); ++it)
    {
      if (i % width() == 0)
	std::cout << std::endl;
      if ((*it).content.empty())
	std::cout << '.';
      else
	std::cout << 'A';
      i++;
    }
  std::cout << std::endl;
}

void	PlayerMap::setPlayer1(APlayer *player1)
{
  _player1 = player1;
}

void	PlayerMap::setPlayer2(APlayer *player2)
{
  _player2 = player2;
}

APlayer	*PlayerMap::getPlayer1()
{
  return _player1;
}

APlayer	*PlayerMap::getPlayer2()
{
  return _player2;
}

APlayer	const *PlayerMap::getPlayer1() const
{
  return _player1;
}

APlayer	const *PlayerMap::getPlayer2() const
{
  return _player2;
}

PlayerMap::~PlayerMap()
{
  PlayerMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content.empty() == false)
	{
	  for (std::list<APlayer *>::iterator it2 = (*it).content.begin();
	       it2 != (*it).content.end();
	       ++it2)
	    delete (*it2);
	}
    }
}

std::string PlayerMap::serialize() const
{

  std::stringstream	ss;
  std::string		tmp;

  tmp = Map::serialize();
  ss << " " << tmp.size() << " " << tmp;
  return (ss.str());
}

void PlayerMap::unserialize(const std::string &str)
{
  std::stringstream	ss(str);
  std::string	tmp;

  Map::unserialize(Serializer::extractSerializable(ss));

  _player1 = 0;
  _player2 = 0;
  for (int i = 0; i < width(); ++i)
    for (int j = 0; j < height(); ++j)
      for (std::list<APlayer*>::iterator it = get(i, j).content.begin();
	   it != get(i, j).content.end(); ++it)
	if (dynamic_cast<Player1*>(*it))
	  _player1 = *it;
	else if (dynamic_cast<Player2*>(*it))
	  _player2 = *it;
}

std::string t_casePlayer::serialize() const
{
  std::string			tmp;
  std::stringstream		ss;
  std::list<APlayer*>::const_iterator	it = content.begin();

  for (; it != content.end(); ++it)
    {
      if (it != content.begin())
	ss << " ";
      tmp = (*it)->serialize();
      ss << typeid(**it).name() << " " << tmp.size() << " " << tmp;
    }
  return (ss.str());
}

void t_casePlayer::unserialize(const std::string &str)
{
  APlayer		*tmp;
  std::stringstream	ss(str);

  while (ss.good())
    {
      std::string id;
      ss >> id;
      tmp = static_cast<APlayer*>
	(static_cast<AObject*>(SerializableFactory::create(id)));
      if (tmp)
	{
	  tmp->initialize();
	  tmp->unserialize(Serializer::extractSerializable(ss));
	  content.push_front(tmp);
	}
    }
}

APlayer		*PlayerMap::getPlayerById(int id)
{
  PlayerMap::iterator	it;

  int		i = 0;
  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content.empty() == false)
	{
	  for (std::list<APlayer *>::iterator it2 = (*it).content.begin();
	       it2 != (*it).content.end();
	       ++it2)
	    if ((*it2)->getId() == id)
	      return *it2;
	}
      i++;
    }
  return (0);
}

bool		PlayerMap::gameEnd() const
{
  PlayerMap::const_iterator	it;
  int			count;

  count = 0;
  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content.empty() == false)
	{
	  count += (*it).content.size();
	  if (count > 1)
	    return false;
	}
    }
  return (true);
}

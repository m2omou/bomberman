//
// Map.hpp for Nibbler in /home/brissa_a//Programme/B4/nmobjdump/nm
//
// Made by alexis brissard
// Login   <brissa_a@epitech.net>
//
// Started on  Tue Mar  6 15:28:09 2012 alexis brissard
// Last update Sun Jun  3 17:01:28 2012 jimmy delas
//

#ifndef __MAP_HPP__
# define __MAP_HPP__

#include "Map.hpp"
#include <string>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>

#include "ISerializable.hpp"
#include "Serializer.hpp"

template <typename U>
class		Map :
  public std::vector<U>,
  public ISerializable
{
private:
  int			_width;
  int			_height;

public:

  Map(int const width = 0, int const height = 0)
  {
    this->resize(width * height);
    _width = width;
    _height = height;
  }

  U		&operator() (int x, int y)
  {
    return get(x, y);
  }

  U		const &operator() (int x, int y) const
  {
    return get(x, y);
  }

  U		&get(int x, int y)
  {
    if (x < 0 || x >= _width ||
	y < 0 || y >= _height)
      {
	std::stringstream	ss;
	ss << "Map:Request out of bound. (" << x << ";" << y << ")" << std::endl;
	throw std::runtime_error(ss.str());
      }
    return (*this)[y * _width + x];
  }

  int		width() const
  {
    return _width;
  }

  int		height() const
  {
    return _height;
  }

  ~Map()
  {
  }

  virtual std::string serialize() const
  {
    std::stringstream ss;
    typename std::vector<U>::const_iterator it = this->begin();
    std::string tmp;

    ss << _width << " " << _height << " ";
    for (; it != this->end() ; ++it)
      {
	tmp = it->serialize();
	ss << tmp.length() << " " << tmp << " ";
      }
    return ss.str();
  }

  virtual void unserialize(const std::string &str)
  {
    std::stringstream ss(str);
    int i = -1;

    ss >> _width >> _height;
    while (++i < _width * _height)
      {
	U data;
	data.unserialize(Serializer::extractSerializable(ss));
	push_back(data);
      }
  }

};

#endif /* MAP_HPP */

#ifndef			__LOADMAP_HPP__
# define		__LOADMAP_HPP__

#include                <iostream>
#include                <fstream>
#include                <string>
#include                <sstream>
#include                <vector>
#include		<stdlib.h>

class			LoadMap
{
public:
  std::vector<std::string>      data;
  unsigned int	width;
  unsigned int	height;

public:
  LoadMap();
  LoadMap(const std::string &file);
  void	select_map(const std::string &file);
  ~LoadMap();
};

#endif

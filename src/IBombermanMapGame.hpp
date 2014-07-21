#ifndef __IBOMBERMANMAP_HPP__
# define __IBOMBERMANMAP_HPP__

#include "TextureBundle.hpp"

class		IBombermanMapGame
{
public:
  virtual TextureBundle			&getTexture() = 0;
  virtual ~IBombermanMapGame() {};
};

#endif /* IBOMBERMANMAP_HPP */

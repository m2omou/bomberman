#ifndef __TEXTUREBUNDLE_HPP__
# define __TEXTUREBUNDLE_HPP__

#include "Image.hpp"

struct		TextureBundle
{
  gdl::Image			woodBox;
  gdl::Image			steelBox;
  gdl::Image			grass;
  gdl::Image			danger;
  gdl::Image			life;
  gdl::Image			trollFace;
  gdl::Image			bombe;
  gdl::Image			explosion;

  TextureBundle();
};

#endif /* TEXTUREBUNDLE_HPP */

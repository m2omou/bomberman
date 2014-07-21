#ifndef __CUBE_HPP__
# define __CUBE_HPP__

#include <string>

#include <GL/gl.h>
#include <GL/glu.h>

#include "AObject.hpp"
#include "Image.hpp"

class		MyGame;

class		Cube : public AObject
{
private:
  gdl::Image	*_tex;

protected:
  Cube(float posx, float posy, float posz,
       float rotx, float roty, float rotz,
       float scale, gdl::Image *tex);
public:
  void			initialize(void);
  void			update();
  void			draw(void);
};

#endif /* CUBE_HPP */

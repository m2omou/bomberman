#ifndef __SQUARE_HPP__
# define __SQUARE_HPP__

#include <string>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Image.hpp"
#include "AObject.hpp"

class		Square : public AObject
{
protected:
  gdl::Image	*_tex;
  float		_repeat;

public:
  Square(float posx, float posy, float posz,
	 float rotx, float roty, float rotz,
	 float scale, gdl::Image *tex, float repeat = 1);
  Square(float posx, float posy, float posz,
	 float rotx, float roty, float rotz,
	 float scalex, float scaley, float scalez,
	 gdl::Image *tex, float repeat);
  Square();
  void		initialize(void);
  void		update();
  void		draw(void);
  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
  void		setRepeat(float value);
  void		setTex(gdl::Image *tex);
};

#endif /* SQUARE_HPP */

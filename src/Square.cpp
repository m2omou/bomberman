#include "Square.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "Serializer.hpp"

Square::Square(float posx, float posy, float posz,
	       float rotx, float roty, float rotz,
	       float scale,
	       gdl::Image *tex, float repeat)
{
  _tex = tex;
  _position.x = posx;
  _position.y = posy;
  _position.z = posz;
  _rotation.x = rotx;
  _rotation.y = roty;
  _rotation.z = rotz;
  _scale.x = scale;
  _scale.y = scale;
  _scale.z = scale;
  _repeat = repeat;
}

Square::Square(float posx, float posy, float posz,
	       float rotx, float roty, float rotz,
	       float scalex, float scaley, float scalez,
	       gdl::Image *tex, float repeat)
{
  _tex = tex;
  _position.x = posx;
  _position.y = posy;
  _position.z = posz;
  _rotation.x = rotx;
  _rotation.y = roty;
  _rotation.z = rotz;
  _scale.x = scalex;
  _scale.y = scaley;
  _scale.z = scalez;
  _repeat = repeat;
}

Square::Square()
{

}

void		Square::initialize(void)
{

}

void		Square::update()
{
}

void		Square::draw(void)
{
  glPushMatrix();
  glTranslatef(_position.x, _position.y, _position.z);
  glRotatef(_rotation.x, 1, 0, 0);
  glRotatef(_rotation.y, 0, 1, 0);
  glRotatef(_rotation.z, 0, 0, 1);
  glScalef(_scale.x, _scale.y, _scale.z);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  if (_tex)
    _tex->bind();
  glBegin(GL_QUADS);
  glTexCoord2f(0, _repeat);
  glVertex3f(-1.0f, 1.0f, 0.0f);
  glTexCoord2f(0, 0);
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glTexCoord2f(_repeat, 0);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glTexCoord2f(_repeat, _repeat);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glEnd();
  glPopMatrix();
}

void		Square::setRepeat(float value)
{
  _repeat = value;
}

std::string Square::serialize() const
{
  std::stringstream ss;
  std::string tmp;

  tmp = AObject::serialize();
  ss << tmp.length() << " " << tmp << " " << _repeat;
  return ss.str();
}

void Square::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  AObject::unserialize(Serializer::extractSerializable(ss));
  ss >> _repeat;
}

void Square::setTex(gdl::Image *tex)
{
  _tex = tex;
}

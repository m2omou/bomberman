#include "Square.hpp"
#include "Cube.hpp"
#include "MyGame.hpp"

Cube::Cube(float posx, float posy, float posz,
	   float rotx, float roty, float rotz,
	   float scale, gdl::Image *tex)
  : AObject()
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
  _boundaryBox = scale;
}

void		Cube::initialize(void)
{
}

void		Cube::update()
{
  
}

void		Cube::draw(void)
{
  static const float	side_param[6][6] =
    {
      { 1, 0, 0, 0,90, 0},
      {-1, 0, 0, 0,90, 0},
      { 0, 1, 0,90, 0, 0},
      { 0,-1, 0,90, 0, 0},
      { 0, 0, 1, 0, 0, 0},
      { 0, 0,-1, 0, 0, 0}
    };
  glPushMatrix();
  glTranslatef(_position.x, _position.y, _position.z);
  glRotatef(_rotation.x, 1, 0, 0);
  glRotatef(_rotation.y, 0, 1, 0);
  glRotatef(_rotation.z, 0, 0, 1);
  glScalef(_scale.x, _scale.y, _scale.z);
  for (int i = 0; i < 6; i++)
    {
      Square		square(side_param[i][0], side_param[i][1], side_param[i][2],
			       side_param[i][3], side_param[i][4], side_param[i][5],
			       1, _tex);
      square.initialize();
      square.draw();
    }
  glPopMatrix();
}

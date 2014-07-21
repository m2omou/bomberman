#pragma once

#include "Cube.hpp"

class		MyGame;

class		SteelBox : public Cube
{
public:
  SteelBox(float posx, float posy, float posz,
	   float rotx, float roty, float rotz,
	   float scale, MyGame *game);
  static AObject  *create(int x, int y, MyGame *game);

};


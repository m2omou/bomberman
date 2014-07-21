#pragma once

#include "Cube.hpp"

class		MyGame;

class		WoodBox : public Cube
{
private:
  MyGame	*_game;
public:
  WoodBox(float posx, float posy, float posz,
	  float rotx, float roty, float rotz,
	  float scale, MyGame *game);
  static AObject  *create(int x, int y, MyGame *game);
  ~WoodBox();
};

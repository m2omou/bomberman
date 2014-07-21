
#include "TextureBundle.hpp"

TextureBundle::TextureBundle()
{
  woodBox = gdl::Image::load("ressources/textures/box.png");
  steelBox = gdl::Image::load("ressources/textures/steel.png");
  grass = gdl::Image::load("ressources/textures/grass.png");
  danger = gdl::Image::load("ressources/textures/danger.png");
  life = gdl::Image::load("ressources/textures/life.png");
  trollFace = gdl::Image::load("ressources/textures/trollface.png");
  bombe = gdl::Image::load("ressources/textures/bombe.png");
  explosion = gdl::Image::load("ressources/textures/fire.png");
}

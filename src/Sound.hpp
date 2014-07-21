//
// Sound.hpp for  in /home/bouly_c//Work/bomberman-2015-wilgen_t/src
//
// Made by clement bouly
// Login   <bouly_c@epitech.net>
//
// Started on  Wed May 30 19:24:44 2012 clement bouly
// Last update Sun Jun  3 19:18:04 2012 alexis brissard
//

#ifndef	SOUND_HPP_
#define	SOUND_HPP_

#include	<cstdlib>
#include	<cstdio>
#include	<iostream>
#include	<string>
#include	"fmod.h"

#define	ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))

enum	SoundType
  {
    BOMB = 0,
    BOX,
    SPEED_BONUS,
    BOMB_BONUS,
    POWER_BONUS,
    DEATH,
    MOVE_MENU,
    VALIDATE_MENU,
    WIN,
    LOSE,
    INTRO
  };

class	Sound
{
  FMOD_SYSTEM	*system;
  FMOD_SOUND	*sound[11];
  FMOD_SOUND	*bg_sound[9];
  FMOD_CHANNEL	*bg_channel;
  int		position;
  float		volume;
  int		nbEffect;
  int		nbMusic;

public:
  Sound();
  ~Sound();
  void	playBackground();
  void	nextBackground();
  void	playSound(SoundType type);
  void	setVolume(float f);
  FMOD_SYSTEM	*getSystem();
  FMOD_RESULT F_CALLBACK onEnd(FMOD_CHANNEL *,
			       FMOD_CHANNEL_CALLBACKTYPE,
			       void *,
			       void *);
};
FMOD_RESULT F_CALLBACK onEnd_s(FMOD_CHANNEL *,
			       FMOD_CHANNEL_CALLBACKTYPE,
			       void *,
			       void *);

#endif

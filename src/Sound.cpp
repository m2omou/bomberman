//
// Sound.cpp for  in /home/bouly_c//Work/bomberman-2015-wilgen_t/src
//
// Made by clement bouly
// Login   <bouly_c@epitech.net>
//
// Started on  Wed May 30 19:24:54 2012 clement bouly
// Last update Sun Jun  3 19:18:18 2012 alexis brissard
//

#include	"Sound.hpp"

Sound::Sound()
{
  char		buf[128];
  std::string	effectSound[] = {"bomb.wav", "cube.wav",
				  "bonus.wav", "bonus.wav",
				  "bonus.wav", "death.wav",
				  "move_menu.wav", "validate.wav",
				 "win.wav", "lose.wav", "intro.wav"};

  volume = 0.2;
  nbEffect = 0;
  nbMusic = 0;
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL);
  for (unsigned int i = 0; i < ARRAY_SIZE(effectSound); i++)
    {
      nbEffect += 1;
      snprintf(buf, 128, "ressources/sounds/%s", effectSound[i].c_str());
      FMOD_System_CreateStream(system, buf, FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &sound[i]);
    }
  srandom(time(NULL));
  position = random() % 9;
  for (unsigned int i = 0; i < 9; i++)
    {
      nbMusic += 1;
      snprintf(buf, 128, "ressources/sounds/%d.mp3", i + 1);
      FMOD_System_CreateStream(system, buf, FMOD_HARDWARE | FMOD_LOOP_OFF | FMOD_2D, 0, &bg_sound[i]);
    }
}

Sound::~Sound()
{
  FMOD_System_Release(system);
  for (int i = 0; i < nbMusic; i++)
    FMOD_Sound_Release(bg_sound[i]);
  for (int i = 0; i < nbEffect; i++)
    FMOD_Sound_Release(sound[i]);
}

void		Sound::playBackground()
{
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bg_sound[position], 0, &bg_channel);
  FMOD_Channel_SetUserData(bg_channel, this);
  FMOD_Channel_SetCallback(bg_channel, onEnd_s);
  FMOD_Channel_SetVolume(bg_channel, volume);
}

void		Sound::nextBackground()
{
  unsigned int i;

  FMOD_Sound_GetLength(bg_sound[position], &i, FMOD_TIMEUNIT_MS);
  FMOD_Channel_SetPosition(bg_channel, i-1,FMOD_TIMEUNIT_MS);
}

FMOD_RESULT F_CALLBACK Sound::onEnd(FMOD_CHANNEL *channel,
				    FMOD_CHANNEL_CALLBACKTYPE,
				    void *,
				    void *)
{
  position = (position + 1 < nbMusic ? position + 1 : 0);
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, bg_sound[position], 0, &channel);
  FMOD_Channel_SetUserData(bg_channel, this);
  FMOD_Channel_SetCallback(bg_channel, onEnd_s);
  FMOD_Channel_SetVolume(bg_channel, volume / 2);
  return (FMOD_OK);
}

FMOD_RESULT F_CALLBACK onEnd_s(FMOD_CHANNEL *channel,
			       FMOD_CHANNEL_CALLBACKTYPE type,
			       void *c1,
			       void *c2)
{
  void *temp = 0;
  FMOD_RESULT result = FMOD_Channel_GetUserData(channel, &temp);
  if (result == FMOD_OK && temp)
    {
      Sound *sound = static_cast<Sound*>(temp);
      return (sound->onEnd(channel, type, c1, c2));
    }
  return result;
}

void		Sound::playSound(SoundType type)
{
  FMOD_CHANNEL	*channel;

  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound[type], 0, &channel);
  FMOD_Channel_SetVolume(channel, 1.0);
}

void		Sound::setVolume(float f)
{
  volume = f;
  FMOD_Channel_SetVolume(bg_channel, volume / 2);
}

FMOD_SYSTEM	*Sound::getSystem()
{
  return (system);
}

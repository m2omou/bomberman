#ifndef __MENU_HPP__
# define __MENU_HPP__

#include <map>
#include <list>
#include <deque>
#include <sstream>
#include "Color.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Square.hpp"
#include "Image.hpp"
#include "Input.hpp"
#include "Text.hpp"
#include "LoadMap.hpp"
#include "ObjectMap.hpp"
#include "Camera.hpp"
#include "Sound.hpp"

#define		INTRO_TIME     	800000

class			Menu : public Square
{
public:
  enum    sub_menu
    {
      Single = 0,
      Multi = 1,
      LoadGame = 2,
      Credit = 3,
      Help = 4,
      Pause = 5,
      Continue = 5,
      Options = 6,
      Help_pause = 7,
      Exit = 8,
      Save = 9,
      DontSave = 10,
      DisplayCredit = 11,
      SelectMap = 12,
      WriteName = 13,
      YouWin = 14,
      GameOver = 15,
      DisplayHelp = 16,
      DisplayLoad = 17,
      Scores = 18,
      DisplayOption = 19,
      DisplayCamera = 20,
      MapHeight = 21,
      MapWidth = 22,
      MapIa = 23
    };

private:
  typedef void (Menu::*action)(MyGame &);
  typedef void (Menu::*displayAction)(gdl::Input &, MyGame &);

  typedef struct	s_menu
  {
    gdl::Image		image;
    Square		square;
    int			index_s;
    int			index_e;
    action		run;
  }			t_menu;

private:
  std::map<sub_menu, displayAction>    	_run;

private:
  sub_menu				button;
  int					release_button;
  t_menu				menu[24];
  t_menu				intro[2];
  gdl::Text				text;
  gdl::Text				map_name;

private:
  std::string				name;
  std::string				map;
  

private:
  bool					view_mode;
  std::list<std::string>		preview_map;
  std::list<std::string>::iterator     	it_map;

private:
  std::list<std::string>		save_file;
  std::list<std::string>::iterator     	it_save;

private:
  LoadMap				*_asciiMap;
  bool					_multi;
  sub_menu     				_lastButton;
  
private:
  float					_sound;
  int					_camera;
  int					_opt;
  gdl::Text				_tsound;
  gdl::Text				_tcamera;

private:
  int					_height;
  int					_width;
  int					_ia;
  int					_edit;
  gdl::Text				_theight;
  gdl::Text				_twidth;
  gdl::Text				_tia;

private:
  gdl::Text				_score;
  gdl::Text				_allScore;
  gdl::Text				_tnameScore;
  std::string				_nameScore;
public:
  Menu();
  ~Menu();
  void		display_menu(gdl::Input &, MyGame &);
  void		key_pressed(gdl::Input &, MyGame &);
  void		key_released(gdl::Input &);
  void		handle_event(const MyGame &, gdl::Input &);
  void		set_menu(t_menu &, const std::string, int, int, const action);
  void		set_button(sub_menu);

public:
  void		run_intro(const MyGame &game, gdl::Window &win);

public:
  void		run_single(MyGame &game);
  void		run_multi(MyGame &game);
  void		run_credit(MyGame &game);
  void		run_help(MyGame &game);
  void		run_continue(MyGame &game);
  void		run_options(MyGame &game);
  void		run_help_pause(MyGame &game);
  void		run_exit(MyGame &game);
  void		run_save(MyGame &game);
  void		run_dontSave(MyGame &game);
  void		run_displayCredit(MyGame &game);
  void		run_sct_map_sgl(MyGame &game);
  void		run_sct_map_mult(MyGame &game);
  void		run_serial(MyGame &game);
  void		run_load_game(MyGame &game);
  void		run_loose(MyGame &game);
  void		run_win(MyGame &game);
  void		run_game(MyGame &game);
  void		run_game_loaded(MyGame &game);

public:
  void		back_menu(MyGame &game);
  void		write_your_name(MyGame &game);
  void		load_map_selected(MyGame &game);
  void		retrieve_map_from_directory();
  void		retrieve_save_from_directory();
  void		event_preview_map(gdl::Input &input, MyGame &game);
  void		write_map_name(MyGame &game);
  void		run(MyGame &game);

public:
  int		stop_press_key(gdl::Input &input);
  void		swap_camera(MyGame &game);
  void		edit_camera(gdl::Input &input, MyGame &game);
  void		edit_option(gdl::Input &input, MyGame &game);
  void		edit_sound(gdl::Input &input, MyGame &game);
  void		edit_map(gdl::Input &input, MyGame &game);
  void		edit_map_height(gdl::Input &input, MyGame &game);
  void		edit_map_width(gdl::Input &input, MyGame &game);
  void		edit_map_ia(gdl::Input &input, MyGame &game);
  void		display_load_game(gdl::Input &input, MyGame &);
  void		display_score(gdl::Input &, MyGame &);
  void		best_score(MyGame &);
  void		write_score_name(MyGame &game, gdl::Input &);
};

#endif

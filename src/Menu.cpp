#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include "Menu.hpp"
#include "MyGame.hpp"
#include "MapWorker.hpp"
#include "PreviewCamera.hpp"
#include "Sound.hpp"

Menu::Menu()
{
  std::string path_intro = "ressources/menu/intro/";
  std::string path_main  = "ressources/menu/main/";
  std::string path_pause = "ressources/menu/pause/";
  std::string path_save = "ressources/menu/save/";
  std::string path_end = "ressources/menu/end/";

  retrieve_map_from_directory();
  retrieve_save_from_directory();
  this->_nameScore.clear();
  this->it_map = this->preview_map.begin();
  this->it_save = this->save_file.begin();
  this->_edit = 0;
  this->_height = 30;
  this->_width = 30;
  this->_ia = 5;
  this->_camera = 1;
  this->_sound = 5;
  this->_opt = 0;
  this->_lastButton = Single;
  this->_multi = false;
  this->view_mode = false;
  this->map.clear();
  this->text.setSize(35);
  this->text.setFont("ressources/ttf/Simpsonfont.ttf");
  this->map_name.setFont("ressources/ttf/gang_wolfik.ttf");
  this->button = Single;
  this->release_button = 0;
  /* Menu init */
  set_menu(intro[0], path_intro + "intro2.jpg", 0, 1, &Menu::run_single);
  set_menu(intro[1], path_intro + "intro1.jpg", 0 ,1, &Menu::run_single);
  set_menu(menu[0], path_main + "main1.jpg", 0, 4, &Menu::run_sct_map_sgl);
  set_menu(menu[1], path_main + "main2.jpg", 0, 4, &Menu::run_sct_map_mult);
  set_menu(menu[2], path_main + "main3.jpg", 0, 4, &Menu::run_load_game);
  set_menu(menu[3], path_main + "main4.jpg", 0, 4, &Menu::run_credit);
  set_menu(menu[4], path_main + "main5.jpg", 0, 4, &Menu::run_help);
  set_menu(menu[5], path_pause + "bomber1.jpg", 5, 8, &Menu::run_continue);
  set_menu(menu[6], path_pause + "bomber2.jpg", 5, 8, &Menu::run_options);
  set_menu(menu[7], path_pause + "bomber3.jpg", 5, 8, &Menu::run_help_pause);
  set_menu(menu[8], path_pause + "bomber4.jpg", 5, 8, &Menu::run_exit);
  set_menu(menu[9], path_pause + "bomber5.jpg", 9, 10, &Menu::run_save);
  set_menu(menu[10], path_pause + "bomber6.jpg", 9, 10, &Menu::run_dontSave);
  set_menu(menu[11], path_main + "bomber5.jpg", 11, 11, &Menu::back_menu);
  set_menu(menu[12], path_main + "bomber6.jpg", 12, 12, &Menu::run);
  set_menu(menu[13], path_save + "bomber.jpg", 13, 13, &Menu::run_serial);
  set_menu(menu[14], path_end + "bomber1.jpg", 14, 14, &Menu::run_loose);
  set_menu(menu[15], path_end + "bomber2.jpg", 15, 15, &Menu::run_win);
  set_menu(menu[16], path_main + "help.jpg", 16, 16, &Menu::back_menu);
  set_menu(menu[17], path_main + "load.jpg", 17, 17, &Menu::run_game_loaded);
  set_menu(menu[18], path_main + "scores.jpg", 18, 18, &Menu::back_menu);
  set_menu(menu[19], path_main + "option1.jpg", 19, 20, &Menu::back_menu);
  set_menu(menu[20], path_main + "option2.jpg", 19, 20, &Menu::back_menu);
  set_menu(menu[21], path_main + "generat1.jpg", 21, 23, &Menu::run_game);
  set_menu(menu[22], path_main + "generat2.jpg", 21, 23, &Menu::run_game);
  set_menu(menu[23], path_main + "generat3.jpg", 21, 23, &Menu::run_game);
  /* init option */
  _run[this->SelectMap] = &Menu::event_preview_map;
  _run[this->DisplayOption] = &Menu::edit_option;
  _run[this->DisplayCamera] = &Menu::edit_option;
  _run[this->MapHeight] = &Menu::edit_map;
  _run[this->MapWidth] = &Menu::edit_map;
  _run[this->MapIa] = &Menu::edit_map;
  _run[this->DisplayLoad] = &Menu::display_load_game;
  _run[this->YouWin] = &Menu::display_score;
  _run[this->GameOver] = &Menu::display_score;
}

Menu::~Menu()
{

}

void		Menu::retrieve_map_from_directory()
{
  DIR		*pDIR;
  struct dirent *entry;
  std::string	map;

  if ((pDIR = opendir("./map")))
    {
      while ((entry = readdir(pDIR)))
	{
	  map = entry->d_name;
	  if ((map.substr(map.find_last_of(".") + 1)) == "map")
	    preview_map.push_front("map/" + map);
	}
      closedir(pDIR);
    }
}

void		Menu::retrieve_save_from_directory()
{
  DIR		*pDIR;
  struct dirent *entry;
  std::string	file;

  if ((pDIR = opendir("./game_saved")))
    {
      while ((entry = readdir(pDIR)))
	{
	  file = entry->d_name;
	  if ((file.substr(file.find_last_of(".") + 1)) == "txt")
	    save_file.push_front("game_saved/" + file);
	}
      closedir(pDIR);
    }
}

void		Menu::set_menu(t_menu &menu, const std::string path,
			       int index_s, int index_e, const action run)
{
  menu.image = gdl::Image::load(path);
  menu.square.setTex(&menu.image);
  menu.square.setPos(0, 0, -20);
  menu.square.setRot(0, 180, 180);
  menu.square.setScale(32, 32, 32);
  menu.square.setRepeat(1);
  menu.index_s = index_s;
  menu.index_e = index_e;
  menu.run = run;
}

void		Menu::set_button(sub_menu _button)
{
  this->button = _button;
}

void		Menu::load_map_selected(MyGame &game)
{
  this->_asciiMap = new LoadMap;
  this->view_mode = false;
  this->release_button = 1;
  this->map = *this->it_map;
  this->_asciiMap->select_map(map);
  game.setFps(30);
  game.setObjectMap(MapWorker::createObjectMap(&game, *_asciiMap));
  game.setCamera(new PreviewCamera(&game));
  game.getObjectMap()->initialize();
  game.getFloor().setScale(_asciiMap->width / 2, _asciiMap->height / 2, 200);
  game.getFloor().setPos(_asciiMap->width / 2, 0, _asciiMap->height / 2);
  game.getFloor().setRepeat(MAX(_asciiMap->width - 2, _asciiMap->height));
  game.getFloor().initialize();
  delete(this->_asciiMap);
}

void		Menu::display_menu(gdl::Input &input, MyGame &game)
{
  std::map<sub_menu, displayAction>::iterator it;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(20.74f, 10.84f, 95.0f, 1.0f);
  glClearDepth(1.0f);
  key_released(input);
  key_pressed(input, game);
  handle_event(game, input);
  glDepthMask(GL_FALSE);
  this->menu[button].square.initialize();
  this->menu[button].square.draw();
  glDepthMask(GL_TRUE);
  (button == WriteName) ? text.draw() : name.clear();
  it = _run.find(button);
  if (it != _run.end())
    (this->*_run[button])(input, game);
}

void		Menu::display_score(gdl::Input &input, MyGame &game)
{
  std::ostringstream	player1;
  std::ostringstream	player2;
  std::string		score;

  player1 << game.getScoreManager().getScorePlayer1();
  player2 << game.getScoreManager().getScorePlayer2();
  score = "Player1: " + player1.str();
  if (game.getScoreManager().getScorePlayer2())
    score += "\n\nPlayer2: " + player2.str();
  _score.setFont("ressources/ttf/light.ttf");
  _score.setText(score);
  _score.setSize(45);
  _score.setPosition(410, 400);
  _score.draw();
  best_score(game);
  write_score_name(game, input);
}

void		Menu::best_score(MyGame &game)
{
  std::map<int, std::string>::const_iterator iter;
  std::stringstream	number;
  std::string		score;
  std::string		save;
  int			limit;

  limit = 0;
  save.clear();
  if (game.getScoreManager().getAllBestScore().size() > 0)
    {
      iter = game.getScoreManager().getAllBestScore().end();
      iter--;
      while (iter != game.getScoreManager().getAllBestScore().begin()
	     && limit < 4)
	{
	  number.str("");
	  score.clear();
	  number << iter->first;
	  score = iter->second;
	  save += score + ":   " + number.str() + "\n";
	  limit++;
	  iter--;
	}
      number << iter->first;
      score = iter->second;
      save += score + ":   " + number.str() + "\n";
      _allScore.setFont("ressources/ttf/light.ttf");
      _allScore.setText(save);
      _allScore.setSize(35);
      _allScore.setPosition(700, 400);
      _allScore.draw();
    }
}

void		Menu::write_score_name(MyGame &game, gdl::Input &input)
{
  int		count;

  count = 0;
  key_released(input);
  while (count <= 26)
    {
      if (game.getInput().isKeyDown(gdl::Keys::Back) && !release_button)
  	{
  	  if (this->_nameScore.size() > 0)
  	    this->_nameScore.erase(this->_nameScore.size() - 1);
  	  this->release_button = 1;
	  game.getSound().playSound(MOVE_MENU);
  	}
      else if (game.getInput().isKeyDown((gdl::Keys::Key)count)
	  && !this->release_button)
      	{
	  if (this->_nameScore.size() < 20)
  	    this->_nameScore += 'A' + count;
  	  this->release_button = 1;
	  game.getSound().playSound(MOVE_MENU);
  	}
      count++;
    }
  this->_tnameScore.setFont("ressources/ttf/light.ttf");
  this->_tnameScore.setSize(35);
  this->_tnameScore.setText(this->_nameScore);
  this->_tnameScore.setPosition(780 - (this->_nameScore.size() * 9), 547);
  this->_tnameScore.draw();
}

void		Menu::run_game_loaded(MyGame &game)
{
  if (save_file.size() > 0)
    {
      game.load(*this->it_save);
      if (game.getPlayerMap())
	{
	  if (game.getPlayerMap()->getPlayer1())
	    game.setCamera(new FollowerCamera(&game, game.getPlayerMap()));
	  game.setLockGame(false);
	}
    }
}

void		Menu::display_load_game(gdl::Input &input, MyGame &game)
{
  gdl::Text	text_name;
  std::string	cut_name;

  if (save_file.size() > 0)
    {
      if (input.isKeyDown(gdl::Keys::Left) && !release_button)
	{
	  if (it_save == save_file.begin())
	    it_save = save_file.end();
	  this->it_save--;
	  this->release_button = 1;
	  game.getSound().playSound(MOVE_MENU);
	}
      else if (input.isKeyDown(gdl::Keys::Right) && !release_button)
	{
	  this->it_save++;
	  if (it_save == save_file.end())
	    it_save = save_file.begin();
	  this->release_button = 1;
	  game.getSound().playSound(MOVE_MENU);
	}
      cut_name = *this->it_save;
      cut_name.erase(cut_name.begin(), cut_name.begin() + 11);
      cut_name.erase(cut_name.end() - 4, cut_name.end());
      text_name.setFont("ressources/ttf/Simpsonfont.ttf");
      text_name.setText(cut_name);
      text_name.setSize(27);
      text_name.setPosition(210, 430);
      text_name.draw();
    }
  else
    {
      text.setText("NO SAVED GAME AVAILABLE");
      text.setSize(40);
      text.setPosition(150, 500);
      text.draw();
    }
}

void		Menu::event_preview_map(gdl::Input &input, MyGame &game)
{
  if (preview_map.size() > 0)
    {
      if ((input.isKeyDown(gdl::Keys::Up) && !release_button)
	  || this->view_mode == true)
	{
	  it_map++;
	  if (it_map == preview_map.end())
	    it_map = preview_map.begin();
	  write_map_name(game);
	}
      else if ((input.isKeyDown(gdl::Keys::Down) && !release_button)
	       || this->view_mode == true)
	{
	  if (it_map == preview_map.begin())
	    it_map = preview_map.end();
	  it_map--;
	  write_map_name(game);
	}
      map_name.draw();
      game.getCamera().update();
      game.getObjectMap()->draw();
      game.getFloor().draw();
    }
  else
    {
      text.setText("THERE IS NO MAP AVAILABLE!");
      text.setSize(40);
      text.setPosition(100, 400);
      text.draw();
    }
}


void		Menu::write_map_name(MyGame &game)
{
  std::string	cut_name;

  load_map_selected(game);
  cut_name = *it_map;
  cut_name.erase(cut_name.begin(), cut_name.begin() + 4);
  cut_name.erase(cut_name.end() - 4, cut_name.end());
  map_name.setText("Name: " + cut_name);
  map_name.setSize(90);
  map_name.setPosition(100, 400);
  game.getSound().playSound(MOVE_MENU);
}

void		Menu::handle_event(const MyGame &game, gdl::Input &input)
{
  if (input.isKeyDown(gdl::Keys::Down)
      && button < menu[button].index_e && !release_button)
    {
      if (button == this->DisplayOption || button == this->DisplayCamera)
	(_opt == 0) ? _opt++ : _opt--;
      else if (button == this->MapHeight || button == this->MapWidth
	       || button == this->MapIa)
	(_edit < 3) ? _edit++ : 1;
      button = static_cast<sub_menu>(button + 1);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  else if (input.isKeyDown(gdl::Keys::Up)
	   && button > menu[button].index_s && !release_button)
    {
      if (button == this->DisplayOption || button == this->DisplayCamera)
	(_opt == 0) ? _opt++ : _opt--;
      else if (button == this->MapHeight || button == this->MapWidth
	       || button == this->MapIa)
	(_edit > 0) ? _edit-- : 1;
      button = static_cast<sub_menu>(button - 1);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
}

void		Menu::key_released(gdl::Input &input)
{
  if (input.isKeyDown(gdl::Keys::Up) == 0
      && input.isKeyDown(gdl::Keys::Down) == 0
      && input.isKeyDown(gdl::Keys::Return) == 0
      && input.isKeyDown(gdl::Keys::Back) == 0
      && input.isKeyDown(gdl::Keys::Space) == 0
      && input.isKeyDown(gdl::Keys::Escape) == 0
      && input.isKeyDown(gdl::Keys::Left) == 0
      && input.isKeyDown(gdl::Keys::Right) == 0
      && stop_press_key(input))
    this->release_button = 0;
}

void		Menu::key_pressed(gdl::Input &input, MyGame &game)
{
  if (input.isKeyDown(gdl::Keys::Return) && !release_button)
    {
      if (*it_map == "map/Edit map.map" && button == this->SelectMap)
	{
	  _edit = 0;
	  button = this->MapHeight;
	}
      else
	(this->*menu[button].run)(game);
      game.getSound().playSound(VALIDATE_MENU);
      this->release_button = 1;
    }
  else if (input.isKeyDown(gdl::Keys::Escape) && !release_button
	   && game.getLockGame() == true)
    {
      if (button > this->Exit && button != this->DisplayOption
	  && button != this->DisplayCamera)
	{
	  button = this->Single;
	  game.getSound().playSound(VALIDATE_MENU);
	}
      release_button = 1;
    }
  if (button == this->WriteName)
    write_your_name(game);
}

int		Menu::stop_press_key(gdl::Input &input)
{
  int		count;

  count = 0;
  while (count <= 26)
    {
      if (input.isKeyDown((gdl::Keys::Key)count) != 0)
	return (0);
      count++;
    }
  this->release_button = 0;
  return (1);
}

void		Menu::write_your_name(MyGame &game)
{
  int		count;

  count = 0;
  while (count <= 26)
    {
      if (game.getInput().isKeyDown(gdl::Keys::Back) && !release_button)
  	{
  	  if (this->name.size() > 0)
  	    this->name.erase(this->name.size() - 1);
  	  this->release_button = 1;
	  game.getSound().playSound(MOVE_MENU);
  	}
      else if (game.getInput().isKeyDown((gdl::Keys::Key)count)
	       && !this->release_button)
      	{
	  if (this->name.size() < 20)
  	    this->name += 'A' + count;
  	  this->release_button = 1;
	  game.getSound().playSound(MOVE_MENU);
  	}
      count++;
    }
  this->text.setText(this->name);
  this->text.setPosition(400 - (this->name.size() * 11), 465);
}

void		Menu::run_save(MyGame &game)
{
  this->button = this->WriteName;
  game.setLockGame(true);
}

void		Menu::run_intro(const MyGame &game, gdl::Window &win)
{
  int		count;

  count = 0;
  game.getSound().playSound(INTRO);
  while (count < 2)
    {
      this->intro[count].square.initialize();
      this->intro[count].square.draw();
      win.display();
      usleep(INTRO_TIME);
      count++;
    }
  game.getSound().playBackground();
}

void		Menu::run_single(MyGame &game)
{
  game.setLockGame(true);
  button = this->Single;
}

void		Menu::run_multi(MyGame &game)
{

  game.setLockGame(true);
  this->button = this->Multi;
}

void		Menu::run(MyGame &game)
{
  game.getSound().nextBackground();
  if (this->preview_map.size() > 0)
    {
      // game.getSound().nextBackground();
      this->_asciiMap = new LoadMap;
      this->_asciiMap->select_map(this->map);
      game.resetCounter();
      game.getScoreManager().reset();
      game.setAsciiMap(*_asciiMap);
      game.setFps(30);
      game.setObjectMap(MapWorker::createObjectMap(&game, *_asciiMap));
      game.setPlayerMap(MapWorker::createPlayerMap(&game, *_asciiMap, _multi));
      game.getPhysicalEngine().setMaps(game.getObjectMap(),
				       game.getPlayerMap());
      game.getFloor().setScale(_asciiMap->width, _asciiMap->height, 200);
      game.getFloor().setPos(_asciiMap->width / 2, 0, _asciiMap->height / 2);
      game.getFloor().setRepeat(MAX(_asciiMap->width, _asciiMap->height));
      if (game.getPlayerMap()->getPlayer1())
	game.setCamera(new FollowerCamera(&game, game.getPlayerMap()));
      game.getObjectMap()->initialize();
      game.getPlayerMap()->initialize();
      game.getFloor().initialize();
      game.setLockGame(false);
      delete(this->_asciiMap);
    }
  else
    button = this->Single;
}

void		Menu::run_credit(MyGame &game)
{
  this->_lastButton = this->Credit;
  game.setLockGame(true);
  this->button = this->DisplayCredit;
}

void		Menu::run_help(MyGame &game)
{
  this->_lastButton = this->Help;
  game.setLockGame(true);
  this->button = this->DisplayHelp;
}

void		Menu::run_continue(MyGame &game)
{
  game.setLockGame(false);
}

void		Menu::run_options(MyGame &game)
{
  this->_opt = 0;
  this->_lastButton = this->Options;
  this->button = this->DisplayOption;
  game.setLockGame(true);
}

void		Menu::run_help_pause(MyGame &game)
{
  this->_lastButton = this->Help_pause;
  game.setLockGame(true);
  this->button = this->DisplayHelp;
}

void		Menu::run_exit(MyGame &game)
{
  game.setLockGame(true);
  this->button = this->Save;
}

void		Menu::run_dontSave(MyGame &game)
{
  this->button = this->Single;
  game.setLockGame(true);
  exit(1);
}

void		Menu::run_displayCredit(MyGame &game)
{
  game.setLockGame(true);
}

void		Menu::run_sct_map_sgl(MyGame &game)
{
  this->view_mode = true;
  this->_multi = false;
  this->button = this->SelectMap;
  game.setLockGame(true);
}

void		Menu::run_sct_map_mult(MyGame &game)
{
  this->view_mode = true;
  this->_multi = true;
  this->button = this->SelectMap;
  game.setLockGame(true);
}

void		Menu::back_menu(MyGame &game)
{
  this->button = _lastButton;
  game.setLockGame(true);
}

void		Menu::run_serial(MyGame &game)
{
  std::ofstream myfile;
  std::string   stime;
  struct tm     *timeinfo;
  time_t        rawtime;
  char          buffer[80];
  int		i;

  i = 0;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 80, "%I_%M_%S_%d_%B_%Y", timeinfo);
  stime = buffer;
  stime = "game_saved/" + name + "-" + stime + ".txt";
  game.save(stime);
  exit(1);
}

void		Menu::run_load_game(MyGame &game)
{
  this->button = this->DisplayLoad;
  game.setLockGame(true);
}

void		Menu::run_loose(MyGame &game)
{
  game.getScoreManager().saveBestScore(_nameScore);
  this->_nameScore.clear();
  this->button = this->Single;
  game.setLockGame(true);
}

void		Menu::run_win(MyGame &game)
{
  game.getScoreManager().saveBestScore(_nameScore);
  this->_nameScore.clear();
  this->button = this->Single;
  game.setLockGame(true);
}

void		Menu::run_game(MyGame &game)
{
  PlayerMap	*tmp;

  game.getSound().nextBackground();
  game.resetCounter();
  game.getScoreManager().reset();
  game.setFps(30);
  game.setObjectMap(MapWorker::createObjectMapAleat(&game, _width, _height, _ia + 2));
  tmp = MapWorker::createPlayerMapAleat(&game, _multi, _width, _height, _ia + 1 + _multi, game.getObjectMap());
  if (tmp == 0)
    {
      delete game.getObjectMap();
      back_menu(game);
      return ;
    }
  game.setPlayerMap(tmp);
  game.getPhysicalEngine().setMaps(game.getObjectMap(),
				   game.getPlayerMap());
  game.getFloor().setScale(_width, _height, 200);
  game.getFloor().setPos(_width / 2, 0, _height / 2);
  game.getFloor().setRepeat(MAX(_width, _height));
  if (game.getPlayerMap()->getPlayer1())
    game.setCamera(new FollowerCamera(&game, game.getPlayerMap()));
  game.getObjectMap()->initialize();
  game.getPlayerMap()->initialize();
  game.getFloor().initialize();
  game.setLockGame(false);

}

void		Menu::edit_sound(gdl::Input &input, MyGame &game)
{
  std::ostringstream convert;

  if (input.isKeyDown(gdl::Keys::Left) && !release_button && !_opt)
    {
      (this->_sound != 0) ? this->_sound-- : 1;
      game.getSound().setVolume(this->_sound / 10);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  else if (input.isKeyDown(gdl::Keys::Right) && !release_button && !_opt)
    {
      (this->_sound != 10) ? this->_sound++ : 1;
      game.getSound().setVolume(this->_sound / 10);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  convert << this->_sound;
  this->_tsound.setText(convert.str());
  this->_tsound.setSize(40);
  this->_tsound.setPosition(548, 345);
  this->_tsound.draw();
}

void		Menu::swap_camera(MyGame &game)
{
  if (this->_camera == 1)
    {
      delete &game.getCamera();
      game.setCamera(new FollowerCamera(&game, game.getPlayerMap()));
    }
  else if (this->_camera == 2)
    {
      delete &game.getCamera();
      game.setCamera(new FreeFlyCamera(&game));
    }
}

void		Menu::edit_camera(gdl::Input &input, MyGame &game)
{
  std::ostringstream convert;

  if (input.isKeyDown(gdl::Keys::Left) && !release_button && _opt)
    {
      (this->_camera != 1) ? this->_camera-- : 1;
      swap_camera(game);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  else if (input.isKeyDown(gdl::Keys::Right) && !release_button && _opt)
    {
      (this->_camera != 2) ? this->_camera++ : 1;
      swap_camera(game);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  convert << this->_camera;
  this->_tcamera.setText(convert.str());
  this->_tcamera.setSize(40);
  this->_tcamera.setPosition(548, 460);
  this->_tcamera.draw();
}

void		Menu::edit_option(gdl::Input &input, MyGame &game)
{
  edit_sound(input, game);
  edit_camera(input, game);
}

void		Menu::edit_map_height(gdl::Input &input, MyGame &game)
{
  std::ostringstream convert;

  if (input.isKeyDown(gdl::Keys::Left) && !release_button && !_edit)
    {
      _height--;
      _height = MAX(_height, 3);
      _ia = MIN(_ia, (_height - 2 + (_height & 1)) * (_width - 2 + (_width & 1)) / 4 - 1 - _multi);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  else if (input.isKeyDown(gdl::Keys::Right) && !release_button && !_edit)
    {
      _height++;
      _height = MIN(_height, 1000);
      _ia = MIN(_ia, (_height - 2 + (_height & 1)) * (_width - 2 + (_width & 1)) / 4 - 1 - _multi);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  convert << this->_height;
  this->_theight.setFont("ressources/ttf/Simpsonfont.ttf");
  this->_theight.setText(convert.str());
  this->_theight.setSize(40);
  this->_theight.setPosition(540, 345);
  this->_theight.draw();
}

void		Menu::edit_map_width(gdl::Input &input, MyGame &game)
{
  std::ostringstream convert;

  if (input.isKeyDown(gdl::Keys::Left) && !release_button && _edit == 1)
    {
      _width--;
      _width = MAX(_width, 3);
      _ia = MIN(_ia, (_height - 2 + (_height & 1)) * (_width - 2 + (_width & 1)) / 4 - 1 - _multi);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  else if (input.isKeyDown(gdl::Keys::Right) && !release_button
	   && _edit == 1)
    {
      _width++;
      _width = MIN(_width, 1000);
      _ia = MIN(_ia, (_height - 2 + (_height & 1)) * (_width - 2 + (_width & 1)) / 4 - 1 - _multi);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  convert << this->_width;
  this->_twidth.setFont("ressources/ttf/Simpsonfont.ttf");
  this->_twidth.setText(convert.str());
  this->_twidth.setSize(40);
  this->_twidth.setPosition(540, 410);
  this->_twidth.draw();
}

void		Menu::edit_map_ia(gdl::Input &input, MyGame &game)
{
  std::ostringstream convert;

  if (input.isKeyDown(gdl::Keys::Left) && !release_button && _edit == 2)
    {
      _ia--;
      _ia = MAX(_ia, 3);
      _ia = MIN(_ia, (_height - 2 + (_height & 1)) * (_width - 2 + (_width & 1)) / 4 - 1 - _multi);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  else if (input.isKeyDown(gdl::Keys::Right)
	   && !release_button && _edit == 2)
    {
      _ia++;
      _ia = MIN(_ia, (_height - 2 + (_height & 1)) * (_width - 2 + (_width & 1)) / 4 - 1 - _multi);
      release_button = 1;
      game.getSound().playSound(MOVE_MENU);
    }
  convert << this->_ia;
  this->_tia.setFont("ressources/ttf/Simpsonfont.ttf");
  this->_tia.setText(convert.str());
  this->_tia.setSize(40);
  this->_tia.setPosition(540, 478);
  this->_tia.draw();
}

void		Menu::edit_map(gdl::Input &input, MyGame &game)
{
  edit_map_height(input, game);
  edit_map_width(input, game);
  edit_map_ia(input, game);
}

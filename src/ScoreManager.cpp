#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Text.hpp"
#include "ScoreManager.hpp"

ScoreManager::ScoreManager()
{
  _scorePlayer1 = 0;
  _scorePlayer2 = 0;
  loadChart();
}

void				ScoreManager::incScorePlayer1(int inc)
{
  _scorePlayer1 += inc;
}

void				ScoreManager::incScorePlayer2(int inc)
{
  _scorePlayer2 += inc;
}

int				ScoreManager::getScorePlayer1() const
{
  return _scorePlayer1;
}

int				ScoreManager::getScorePlayer2() const
{
  return _scorePlayer2;
}

void				ScoreManager::loadChart()
{
  std::map<int, std::string>::const_iterator	it;
  std::ifstream		file("ressources/score");
  int		score;
  std::string	name;

  while (!file.eof() && file.is_open() && file.good())
    {
      file >> score >> name;
      if (!file.eof() && file.is_open() && file.good())
	_chart[score] = name;
    }
}

void				ScoreManager::saveChart() const
{
  std::map<int, std::string>::const_iterator	it;
  std::ofstream		file("ressources/score");

  for (it = _chart.begin(); it != _chart.end(); ++it)
    file << it->first << " " << it->second << std::endl;;
}

bool				myInferior(std::pair<int, std::string> i,
					   std::pair<int, std::string> j)
{
  return i.first < j.first;
}

bool				mySuperior(std::pair<int, std::string> i,
					   std::pair<int, std::string> j)
{
  return i.first < j.first;
}

void				ScoreManager::saveBestScore(std::string const &name)
{
  if (_scorePlayer1 > min_element(_chart.begin(), _chart.end(), mySuperior)->first)
    {
      _chart[_scorePlayer1] = name;
      _chart.erase(min_element(_chart.begin(), _chart.end(), mySuperior)->first);
    }
}

void				ScoreManager::reset()
{
  _scorePlayer1 = 0;
  _scorePlayer2 = 0;
}

void				ScoreManager::dump() const
{
  std::map<int, std::string>::const_iterator	it;

  for (it = _chart.begin(); it != _chart.end(); ++it)
    std::cout << it->first << " " << it->second << std::endl;
}

void				ScoreManager::draw() const
{
  gdl::Text		text_name;
  std::stringstream	str;

  str << "score: " << _scorePlayer1 << std::endl;
  text_name.setFont("ressources/ttf/Simpsonfont.ttf");
  text_name.setText(str.str().c_str());
  text_name.setSize(27);
  text_name.setPosition(150, 0);
  text_name.draw();
}

std::map<int, std::string> const	&ScoreManager::getAllBestScore() const
{
  return _chart;
}

ScoreManager::~ScoreManager()
{
  saveChart();
}

std::string ScoreManager::serialize() const
{
  std::stringstream ss;

  ss << _scorePlayer1 << " " << _scorePlayer2;
  return ss.str();
}

void ScoreManager::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  ss >> _scorePlayer1 >> _scorePlayer2;
}

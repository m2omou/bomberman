#ifndef __SCOREMANAGER_HPP__
# define __SCOREMANAGER_HPP__

#include <map>
#include <string>
#include "ISerializable.hpp"

class		ScoreManager : public ISerializable
{
private:
  int				_scorePlayer1;
  int				_scorePlayer2;
  std::map<int, std::string>	_chart;

public:
  ScoreManager();
  void				incScorePlayer1(int inc);
  void				incScorePlayer2(int inc);
  int				getScorePlayer1() const;
  int				getScorePlayer2() const;
  void				loadChart();
  void				saveChart() const;
  void				saveBestScore(std::string const &name);
  void				reset();
  void				dump() const;
  void				draw() const;
  std::map<int, std::string> const	&getAllBestScore() const;
  ~ScoreManager();

  virtual std::string serialize() const;
  virtual void unserialize(const std::string &);
};

#endif /* SCOREMANAGER_HPP */

#ifndef __OBJECTMAP_HPP__
# define __OBJECTMAP_HPP__

#include "Map.hpp"
#include "ISerializable.hpp"

class		AObject;

typedef	struct		s_caseObject : public ISerializable
{
  AObject		*content;
  AObject		*getContent() { return (content); }

  virtual std::string serialize() const;
  virtual void unserialize(const std::string &str);
}			t_caseObject;

class		ObjectMap
  : public Map<t_caseObject>
{
public:
  ObjectMap(int width, int height);
  virtual ~ObjectMap();
  void	initialize(void);
  void	update();
  void	draw(void);
};

#endif /* OBJECTMAP_HPP */

#include "ObjectMap.hpp"
#include "AObject.hpp"
#include <typeinfo>
#include "SerializableFactory.hpp"

ObjectMap::ObjectMap(int width, int height)
  : Map(width, height)
{
}


void	ObjectMap::initialize(void)
{
  ObjectMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content != 0)
  	(*it).content->initialize();
    }
}

void	ObjectMap::update()
{
  ObjectMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content != 0)
  	(*it).content->update();
    }
}

void	ObjectMap::draw(void)
{
  ObjectMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content != 0)
  	(*it).content->draw();
    }
}

ObjectMap::~ObjectMap()
{
  ObjectMap::iterator	it;

  for (it = this->begin(); it != this->end(); ++it)
    {
      if ((*it).content != 0)
	delete (*it).content;
    }
}

std::string t_caseObject::serialize() const
{
  std::stringstream ss;

  if (content)
    {
      std::string tmp = content->serialize();
      ss << typeid(*content).name() << " " << tmp.size() << " " << tmp;
      return ss.str();
    }
  return "null";
}

void t_caseObject::unserialize(const std::string &str)
{
  std::stringstream ss(str);

  if (!str.compare("null"))
    content = 0;
  else
    {
      std::string tmp;

      ss >> tmp;
      content = static_cast<AObject*>(SerializableFactory::create(tmp));
      content->initialize();
      content->unserialize(Serializer::extractSerializable(ss));
    }
}

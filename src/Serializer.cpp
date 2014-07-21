#include <fstream>
#include <typeinfo>
#include <iostream>
#include <sstream>

#include "Serializer.hpp"
#include "SerializableFactory.hpp"

Serializer::Serializer()
{

}

Serializer::~Serializer()
{

}

Serializer &Serializer::operator<<(ISerializable *s)
{
  map::iterator it = _data.begin();

  it = _data.insert(it, pair(typeid(s).name(),
			 std::list<ISerializable *>()));
  it->second.push_back(s);
  return (*this);
}

void Serializer::pack(const std::string &file)
{
  std::ofstream os(file.c_str(), std::ios::trunc | std::ios::out);
  map::iterator mapit = _data.begin();
  std::list<ISerializable *>::iterator it;

  for (; mapit != _data.end(); ++mapit)
    for (it = mapit->second.begin(); it != mapit->second.end() ; ++it)
      {
	std::string s = (*it)->serialize();
	os << typeid(**it).name() << " " << s.length() << " ";
	os.write(s.c_str(), s.length());
      }
  _data.clear();
  os.close();
}

void Serializer::unpack(const std::string &file)
{
  std::ifstream is(file.c_str(), std::ios::in);
  std::string	className;

  _out.clear();
  while (is.good())
    {
      is >> className;
      if (is.good())
	_out[className] = extractSerializable(is);
    }
  is.close();
}

std::string Serializer::getNextSerializableString(const std::string &str)
{
  map_out::iterator it = _out.find(str);

  if (it != _out.end())
    return it->second;
  return "null";
}

int Serializer::size() const
{
  return _data.size();
}

std::string Serializer::extractSerializable(std::istream &ss)
{
  int			siz;
  char			*buf;

  ss >> siz;
  ss.ignore();
  buf = new char[siz];
  ss.read(buf, siz);

  return std::string(buf, siz);
}

ISerializable *Serializer::getNextSerializable(const std::string &str)
{
  map_out::iterator it = _out.find(str);
  ISerializable *ret;

  if (it != _out.end())
    {
      ret = SerializableFactory::create(str);
      if (ret)
	ret->unserialize(it->second);
      return ret;
    }
  return 0;
}

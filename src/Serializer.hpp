#ifndef __SERIALIZER_HPP__
#define __SERIALIZER_HPP__

#include <map>
#include <list>
#include <typeinfo>
#include "ISerializable.hpp"

class Serializer
{

  typedef std::map<std::string, std::list<ISerializable *> > map;
  typedef std::map<std::string, std::string> map_out;
  typedef std::pair<std::string, std::list<ISerializable *> > pair;

  map _data;
  map_out _out;

public:

  Serializer();
  virtual ~Serializer();

  Serializer &operator<<(ISerializable *);

  void pack(const std::string &file);
  void unpack(const std::string &file);

  std::string getNextSerializableString(const std::string &);

  ISerializable *getNextSerializable(const std::string &);

  int size() const;

  template <class U>
  std::string id() const
  {
    return typeid(U).name();
  }

  static std::string extractSerializable(std::istream &);
};

#endif

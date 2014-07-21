#ifndef __ISERIALIZABLE_HPP__
#define __ISERIALIZABLE_HPP__

#include <string>

class ISerializable
{
public:
  virtual ~ISerializable() {};
  virtual std::string serialize() const = 0;
  virtual void unserialize(const std::string &) = 0;
};

#endif

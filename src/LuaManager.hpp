#ifndef __LUAMANAGER_HPP__
# define __LUAMANAGER_HPP__

#include <lua.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <SLB/Manager.hpp>
#include <SLB/Class.hpp>
#include <SLB/Script.hpp>

class LuaManager
{
public:
  struct MyScript : public SLB::Script
  {
    MyScript(const std::string &fileName);

    template <class T>
    void			call(T o, const std::string &name)
    {
      lua_State *L = getState();
      SLB::LuaCall<void(T)> call(L, name.c_str());
      call(o);
    }
  };

public:
  LuaManager(void (*)(SLB::Manager *));
  ~LuaManager();

  void			runScript(const std::string &);
  void			addGlobalVar(const std::string &, int);
  void			addFunction(const std::string &, const lua_CFunction fun);
  void			printLastError(void);

  class LuaException : public std::exception
  {
  public:
    LuaException();
    LuaException(const LuaException &);
    virtual ~LuaException() throw();

    const char*		what() const throw();

  private:
    std::string		_msg;
  };

private:
  lua_State		*L;
  int			_lastResult;
  bool			_ready;
};

#endif /*__LUAMANAGER_HPP__*/

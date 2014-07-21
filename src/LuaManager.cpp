#include "LuaManager.hpp"

LuaManager::LuaManager(void (*initFun)(SLB::Manager *))
  : L(luaL_newstate()), _lastResult(0), _ready(false)
{
  luaL_openlibs(L);
  SLB::Manager::defaultManager()->registerSLB(L);
  initFun(SLB::Manager::defaultManager());
}

LuaManager::~LuaManager()
{
  lua_pop(L, 1);
  lua_close(L);
}
void		LuaManager::printLastError(void)
{
  std::cerr << lua_tostring(L, -1) << std::endl;
  lua_pop(L, 1);
}

void		LuaManager::addGlobalVar(const std::string &name, int value)
{
  lua_pushnumber(L, value);
  lua_setglobal(L, name.c_str());
}

void		LuaManager::addFunction(const std::string &name,
					const lua_CFunction fun)
{
  lua_register(L, name.c_str(), fun);
}

LuaManager::MyScript::MyScript(const std::string &fileName)
{
  std::ifstream iFile((fileName + ".lua").c_str());
  std::string	str(std::istreambuf_iterator<char>(iFile),
		  (std::istreambuf_iterator<char>()));
  doString(str);
}

void		LuaManager::runScript(const std::string &fileName)
{
  if (luaL_loadfile(L, (fileName + ".lua").c_str()))
    {
      LuaManager::printLastError();
      throw new LuaException;
    }
  if (lua_pcall(L, 0, LUA_MULTRET, 0))
    {
      LuaManager::printLastError();
      throw new LuaException;
    }
}

/*
 *	LuaException
 */

LuaManager::LuaException::LuaException()
  : _msg("Lua exception occured.")
{
}

LuaManager::LuaException::LuaException(const LuaException &o)
  : _msg(o._msg)
{
}

LuaManager::LuaException::~LuaException() throw()
{

}

const char*		LuaManager::LuaException::what() const throw()
{
  return _msg.c_str();
};

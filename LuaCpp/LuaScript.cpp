#include <exception>

#include "lua.hpp"
#include "LuaScript.h"

Lua::Script::Script(const std::string & scriptFileName) : mScriptFileName(scriptFileName)
{
	_load();
}

void Lua::Script::_load()
{
	mState = luaL_newstate();
	luaL_openlibs(mState);

	int error = luaL_loadfile(mState, mScriptFileName.c_str());

	if (error == LUA_ERRSYNTAX)
		throw std::exception((std::string("Error in Syntax of Script ") + mScriptFileName).c_str());
	else if (error == LUA_ERRMEM)
		throw std::exception("Lua memory allocation error");
	else if (error != 0)
		throw std::exception("Unknown Lua error");

	error = lua_pcall(mState, 0, LUA_MULTRET, 0);

	if (error != 0)
		throw std::exception((std::string("Error running the script ") + mScriptFileName).c_str());
}

Lua::Script::~Script()
{
	lua_close(mState);
}

void Lua::Script::reload()
{
	lua_close(mState);
	mState = nullptr;

	_load();
}

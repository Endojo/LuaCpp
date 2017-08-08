#include <exception>

#include "lua.hpp"
#include "LuaScript.h"
#include "LuaLibrary.h"

namespace Lua
{

	Script::Script(const std::string & scriptFileName) : mScriptFileName(scriptFileName)
	{
		_load();
	}

	Script::~Script()
	{
		lua_close(mState);
	}

	void Script::addLibrary(const Library &lib)
	{
		lib.inject(mState);
	}

	void Script::reload()
	{
		lua_close(mState);
		mState = nullptr;

		_load();
	}

	void Script::operator() (const std::string &functionName, std::vector<Lua::Value> args)
	{
		//save number of values on stack
		//so the number of return values can be evaluated
		int stackTopBefore = lua_gettop(mState);

		//load requested function
		lua_getglobal(mState, functionName.c_str());

		//check if we actually got a funciton
		if (!lua_isfunction(mState, -1))
			throw std::exception((mScriptFileName + " -> " + functionName + ": this function does not exist").c_str());

		//push arguments to stack
		for (auto it = args.begin(); it != args.end(); ++it)
			it->pushToState(mState);

		//run function
		int error = lua_pcall(mState, args.size(), LUA_MULTRET, 0);

		if (error != 0)
			throw std::exception((mScriptFileName + " -> " + functionName + ": error running function").c_str());

		//get return values
		std::vector<Lua::Value> returnValues;
		while (lua_gettop(mState) > stackTopBefore)
		{
			returnValues.push_back(Value(mState));
		}
	}

	void Script::_load()
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
}
#pragma once

#include <string>
#include <vector>
#include <utility>

#include "lua.hpp"

#include "LuaValue.h"

struct lua_State;

namespace Lua
{
	class Script
	{
	public:
		Script(const std::string &scriptFileName);
		~Script();

		void reload();

		void operator() (const std::string &functionName, std::vector<Lua::Value> args = std::vector<Lua::Value>())
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
		lua_State *mState;

	private:
		void _load();

		const std::string mScriptFileName;
	};

}
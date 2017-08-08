#pragma once

#include <string>
#include <vector>
#include <utility>

#include "lua.hpp"

#include "LuaValue.h"

struct lua_State;

namespace Lua
{
	class Library;

	class Script
	{
	public:
		Script(const std::string &scriptFileName);
		~Script();

		void addLibrary(const Library &lib);

		void reload();

		void operator() (const std::string &functionName, std::vector<Lua::Value> args = std::vector<Lua::Value>());

	private:
		lua_State *mState;
		void _load();

		const std::string mScriptFileName;
	};

}
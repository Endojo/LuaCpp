#pragma once

#include <string>
#include <map>

struct lua_State;

namespace Lua
{
	//inherit from this, expose your functions via the constructor to lua
	//add to any script that wants to access this library
	class Library
	{
	public:
		Library(const std::string &name, void* classInstance, const std::map<std::string, int(*)(lua_State*)> &functionList);

		//call to inject all functions into a lua_State
		void inject(lua_State *L) const;

		const std::string mName;

	private:
		void *mClassInstance;
		const std::map<std::string, int(*)(lua_State*)> mFunctionList;
	};
}
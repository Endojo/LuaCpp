#include "LuaLibrary.h"
#include "lua.hpp"

namespace Lua
{
	Library::Library(const std::string &name, void* classInstance, const std::map<std::string, int(*)(lua_State*)> &functionList)
		: mName(name)
		, mClassInstance(classInstance)
		, mFunctionList(functionList)
	{
	}

	void Library::inject(lua_State *L) const
	{
		luaL_Reg *functionList = new luaL_Reg[mFunctionList.size() + 1];

		int i = 0;
		for (auto it = mFunctionList.begin(); it != mFunctionList.end(); ++it)
		{
			functionList[i].name = it->first.c_str();
			functionList[i].func = it->second;
			i++;
		}

		//sentinel
		functionList[i] = { nullptr, nullptr };

		//add library
		lua_newtable(L);
		lua_pushlightuserdata(L, mClassInstance);
		luaL_setfuncs(L, functionList, 1);
		lua_setglobal(L, mName.c_str());

		delete[] functionList;
	}
}
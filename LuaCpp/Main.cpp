#include <iostream>
#include <string>
#include "LuaScript.h"
#include "LuaFunction.h"

struct Foo
{
	float bar(std::string str)
	{
		std::cout << str << std::endl;
		return 6.9f;
	}

	Lua::Value bar(Lua::Value str)
	{
		return bar(static_cast<std::string>(str));
	}
};



int main()
{
	Lua::Script testscript("C:\\Users\\Jonathan\\Desktop\\Testscript.lua");

	testscript("pimmel");
	testscript("drucken", { "Dies ist ein Dummer Testtext!" });

	Foo fo;

	//inject the function into the script
	luaL_Reg *functionList = new luaL_Reg[2];

	//functionList[0] = { "bar", Lua::FunctionWrapper<Foo, float, std::string, &Foo::bar> };
	functionList[0] = { "bar", Lua::Function<Foo, &Foo::bar> };
	functionList[1] = { nullptr, nullptr };

	//add library
	lua_newtable(testscript.mState);
	lua_pushlightuserdata(testscript.mState, &fo);
	luaL_setfuncs(testscript.mState, functionList, 1);
	lua_setglobal(testscript.mState, "Foo");

	delete[] functionList;

	testscript("test", { "Halli hallo!" });

	std::cin.get();

	return 0;
}
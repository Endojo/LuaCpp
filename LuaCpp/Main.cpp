#include <iostream>
#include "LuaScript.h"
#include "LuaFunction.h"

void wrapThis(int i)
{
	std::cout << i << std::endl;
}

int main()
{
	Lua::Script testscript("C:\\Users\\Jonathan\\Desktop\\Testscript.lua");

	testscript("pimmel");
	testscript("drucken", { "Dies ist ein Dummer Testtext!" });

	std::function<void(int)> func = std::bind(wrapThis, Lua::Value(nullptr, 1));

	std::cin.get();

	return 0;
}
#include <iostream>
#include <string>
#include "LuaScript.h"
#include "LuaFunction.h"
#include "LuaLibrary.h"

struct Foo : public Lua::Library
{
	Foo() : Library("Foo", this, {
		{ "bar", Lua::Function<Foo, &Foo::bar>}
	})
	{
	}

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
	testscript.addLibrary(fo);

	testscript("test", { "Halli hallo!" });

	std::cin.get();

	return 0;
}
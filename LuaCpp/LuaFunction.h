#pragma once

#include "lua.hpp"
#include "LuaValue.h"
#include <vector>

namespace Lua
{
	//Implementations of the function wrapper
	//dependent on the function signature


	// ARGUMENT: vector<Value>


	// RETURN: vector<Value>

	template <typename TOwner, std::vector<Value>(TOwner::*func)(std::vector<Value>&)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));
		std::vector<Value> arguments, returnValues;

		//get arguments
		int count = lua_gettop(L);
		for (int i = 1; i <= count; ++i)
			arguments.push_back(Value(L, i));

		//call wrapped function
		returnValues = (owner->*func)(arguments);

		//push return values
		for (auto it = returnValues.begin(); it != returnValues.end(); ++it)
			it->pushToState(L);

		//return number of return values
		return size;
	}

	template <std::vector<Value>(*func)(std::vector<Value>&)>
	int Function(lua_State *L)
	{
		std::vector<Value> arguments, returnValues;

		//get arguments
		int count = lua_gettop(L);
		for (int i = 1; i <= count; ++i)
			arguments.push_back(Value(L, i));

		//call wrapped function
		returnValues = (*func)(arguments);

		//push return values
		for (auto it = returnValues.begin(); it != returnValues.end(); ++it)
			it->pushToState(L);

		//return number of return values
		return size;
	}


	// RETURN: Value

	template <typename TOwner, Value(TOwner::*func)(std::vector<Value>&)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));
		std::vector<Value> arguments;

		//get arguments
		int count = lua_gettop(L);
		for (int i = 1; i <= count; ++i)
			arguments.push_back(Value(L, i));

		//call wrapped function
		Value returnValue = (owner->*func)(arguments);

		//push return value
		returnValue.pushToState(L);

		//return number of return values
		return 1;
	}

	template <Value(*func)(std::vector<Value>&)>
	int Function(lua_State *L)
	{
		std::vector<Value> arguments;

		//get arguments
		int count = lua_gettop(L);
		for (int i = 1; i <= count; ++i)
			arguments.push_back(Value(L, i));

		//call wrapped function
		Value returnValue = (*func)(arguments);

		//push return value
		returnValue.pushToState(L);

		//return number of return values
		return 1;
	}


	// RETURN: void

	template <typename TOwner, void(TOwner::*func)(std::vector<Value>&)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));
		std::vector<Value> arguments;

		//get arguments
		int count = lua_gettop(L);
		for (int i = 1; i <= count; ++i)
			arguments.push_back(Value(L, i));

		//call wrapped function
		(owner->*func)(arguments);

		//return number of return values
		return 0;
	}

	template <void(*func)(std::vector<Value>&)>
	int Function(lua_State *L)
	{
		std::vector<Value> arguments;

		//get arguments
		int count = lua_gettop(L);
		for (int i = 1; i <= count; ++i)
			arguments.push_back(Value(L, i));

		//call wrapped function
		(*func)(arguments);

		//return number of return values
		return 0;
	}




	// ARGUMENT: Value


	// RETURN: vector<Value>

	template <typename TOwner, std::vector<Value>(TOwner::*func)(Value)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));
		std::vector<Value> returnValues;

		//get argument
		Value argument(L, i);

		//call wrapped function
		returnValues = (owner->*func)(argument);

		//push return values
		for (auto it = returnValues.begin(); it != returnValues.end(); ++it)
			it->pushToState(L);

		//return number of return values
		return size;
	}

	template <std::vector<Value>(*func)(Value)>
	int Function(lua_State *L)
	{
		std::vector<Value> returnValues;

		//get argument
		Value argument(L, i);

		//call wrapped function
		returnValues = (*func)(argument);

		//push return values
		for (auto it = returnValues.begin(); it != returnValues.end(); ++it)
			it->pushToState(L);

		//return number of return values
		return size;
	}


	// RETURN: Value

	template <typename TOwner, Value(TOwner::*func)(Value)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));

		//get argument
		Value argument(L, 1);

		//call wrapped function
		Value returnValue = (owner->*func)(argument);

		//push return value
		returnValue.pushToState(L);

		//return number of return values
		return 1;
	}

	template <Value(*func)(Value)>
	int Function(lua_State *L)
	{
		//get argument
		Value argument(L, 1);

		//call wrapped function
		Value returnValue = (*func)(argument);

		//push return value
		returnValue.pushToState(L);

		//return number of return values
		return 1;
	}


	// RETURN: void

	template <typename TOwner, void(TOwner::*func)(Value)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));

		//get argument
		Value argument(L, 1);

		//call wrapped function
		(owner->*func)(argument);

		//return number of return values
		return 0;
	}

	template <void(*func)(Value)>
	int Function(lua_State *L)
	{
		//get argument
		Value argument(L, 1);

		//call wrapped function
		(*func)(argument);

		//return number of return values
		return 0;
	}




	// ARGUMENT: Void


	// RETURN: vector<Value>

	template <typename TOwner, std::vector<Value>(TOwner::*func)(void)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));
		std::vector<Value> returnValues;

		//call wrapped function
		returnValues = (owner->*func)();

		//push return values
		for (auto it = returnValues.begin(); it != returnValues.end(); ++it)
			it->pushToState(L);

		//return number of return values
		return size;
	}

	template <std::vector<Value>(*func)(void)>
	int Function(lua_State *L)
	{
		std::vector<Value> returnValues;

		//call wrapped function
		returnValues = (*func)();

		//push return values
		for (auto it = returnValues.begin(); it != returnValues.end(); ++it)
			it->pushToState(L);

		//return number of return values
		return size;
	}


	// RETURN: Value

	template <typename TOwner, Value(TOwner::*func)(void)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));

		//call wrapped function
		Value returnValue = (owner->*func)();

		//push return value
		returnValue.pushToState(L);

		//return number of return values
		return 1;
	}

	template <Value(*func)(void)>
	int Function(lua_State *L)
	{
		//call wrapped function
		Value returnValue = (*func)();

		//push return value
		returnValue.pushToState(L);

		//return number of return values
		return 1;
	}


	// RETURN: void

	template <typename TOwner, void(TOwner::*func)(void)>
	int Function(lua_State *L)
	{
		TOwner *owner = reinterpret_cast<TOwner*>(lua_touserdata(L, lua_upvalueindex(1)));

		//call wrapped function
		(owner->*func)();

		//return number of return values
		return 0;
	}

	template <void(*func)(void)>
	int Function(lua_State *L)
	{
		//call wrapped function
		(*func)();

		//return number of return values
		return 0;
	}
}
#include <exception>
#include "LuaValue.h"

#include "lua.hpp"


namespace Lua
{
	Value::Value(double number)
	{
		mType = Type::number;
		mNumber = number;
	}

	Value::Value(bool boolean)
	{
		mType = Type::boolean;
		mBoolean = boolean;
	}

	Value::Value(const std::string &string)
	{
		mType = Type::string;
		mString = string;
	}
	Value::Value(const char *string)
	{
		mType = Type::string;
		mString = string;
	}

	Value::Value(Type type)
	{
		mType = type;
	}

	Value::Value(lua_State * L, int idx)
	{
		pullFromState(L, idx);
	}

	Value::operator double() const
	{
		if (mType != Type::number)
			throw std::exception("Can't convert value to double", (int)mType);

		return mNumber;
	}

	Value::operator bool() const
	{
		if (mType != Type::boolean)
			throw std::exception("Can't convert value to bool", (int)mType);

		return mBoolean;
	}

	Value::operator std::string() const
	{
		if (mType != Type::string)
			throw std::exception("Can't convert value to string", (int)mType);

		return mString;
	}

	Value::operator Type() const
	{
		return mType;
	}


	Value& Value::operator=(const double& right)
	{
		mType = Type::number;
		mNumber = right;
		return *this;
	}

	Value& Value::operator=(const bool& right)
	{
		mType = Type::boolean;
		mBoolean = right;
		return *this;
	}

	Value& Value::operator=(const std::string& right)
	{
		mType = Type::string;
		mString = right;
		return *this;
	}
	Value& Value::operator=(const char *right)
	{
		mType = Type::string;
		mString = right;
		return *this;
	}

	Value& Value::operator=(const Type& right)
	{
		mType = right;
		return *this;
	}


	void Value::pushToState(lua_State *L) const
	{
		switch (mType)
		{
		case Type::nil:
			lua_pushnil(L);
			break;
		case Type::boolean:
			lua_pushboolean(L, mBoolean);
			break;
		case Type::number:
			lua_pushnumber(L, mNumber);
			break;
		case Type::string:
			lua_pushstring(L, mString.c_str());
			break;
		default:
			break;
		}
	}

	void Value::pullFromState(lua_State *L, int idx)
	{
		switch (lua_type(L, idx))
		{
		case LUA_TBOOLEAN:
			mType = Type::boolean;
			mBoolean = (bool)lua_toboolean(L, idx);
			break;
		case LUA_TNUMBER:
			mType = Type::number;
			mNumber = lua_tonumber(L, idx);
			break;
		case LUA_TSTRING:
			mType = Type::string;
			mString = lua_tostring(L, idx);
			break;
		case LUA_TNIL:
			mType = Type::nil;
			break;
		case LUA_TFUNCTION:
			mType = Type::function;
			break;
		case LUA_TTABLE:
			mType = Type::table;
			break;
		case LUA_TLIGHTUSERDATA:
			mType = Type::userdata;
			break;
		case LUA_TUSERDATA:
			mType = Type::userdata;
			break;
		case LUA_TTHREAD:
			mType = Type::thread;
			break;
		}
	}
}
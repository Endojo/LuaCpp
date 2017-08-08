#pragma once

#include <string>

struct lua_State;

namespace Lua
{

	struct Value
	{
		enum class Type
		{
			nil, boolean, number, string, userdata, function, thread, table
		};

		Value(double number);
		Value(bool boolean);
		Value(const std::string &string);
		Value(const char *string);
		Value(Type type = Type::nil);

		//pulls from state
		Value(lua_State *L, int idx = -1);

		operator double() const;
		operator bool() const;
		operator std::string() const;
		operator Type() const;

		Value& operator=(const double& right);
		Value& operator=(const bool& right);
		Value& operator=(const std::string& right);
		Value& operator=(const char* right);
		Value& operator=(const Type& right);

		void pushToState(lua_State *L) const;
		void pullFromState(lua_State *L, int idx = -1);

	private:

		double mNumber;
		bool mBoolean;
		std::string mString;
		Type mType;
	};
}
#pragma once

#include <functional>

namespace Lua
{
	template<T t, std::function<T(void)> *func>
	int Wrapper
}
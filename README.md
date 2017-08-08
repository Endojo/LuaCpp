# LuaCpp

A (hopefully) simple wrapper to integrate Lua into any C++ project.
Intended to easily call Lua routines from C++ at any time, allowing them to use C++ functions.

That way, the low-level stuff can be implemented in C++, but the high-level usage can be written in lua, allowing faster iteration times and reloading of the scripts while the program is running.

If lua itself is already set up, just include the files / build a lib and link to it.


## Usage

Lua::Script script(path_to_script);
initialises a script (runs all global functions)

script("Function_Name", {parameters, ...});
executes the requested function


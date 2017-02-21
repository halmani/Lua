cmake_minimum_required(VERSION 3.7.2)
add_lib(LuaLibrary STATIC
	${CMAKE_CURRENT_LIST_DIR}/lua-5.3.4/
	PARENT_SCOPE)

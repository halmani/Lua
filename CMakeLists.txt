cmake_minimum_required(VERSION 2.8)
#project(LuaSample)

#set(LuaSample_VERSION_MAJOR 0)
#set(LuaSample_VERSION_MINOR 1)

#configure_file(
#	"${PROJECT_SOURCE_DIR}/LuaSampleConfig.h.in"
#	"${PROJECT_BINARY_DIR}/LuaSampleConfig.h"
#	)

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(./src)
add_executable(LuaSample ${LuaSample_SRC})

cmake_minimum_required(VERSION 3.7.2)
project(LuaSample)

set(LuaSample_VERSION_MAJOR 0)
set(LuaSample_VERSION_MINOR 1)

add_subdirectory(src)
#add_subdirectory(lib)
add_executable(LuaSample ${LuaSample_SRC})
set(CMAKE_BUILD_TYPE Debug)

# links
include_directories(lib/lua-5.3.4/install/include)
find_library(lua NAMES liblua.a PATHS lib/lua-5.3.4/install/lib)
target_link_libraries(LuaSample ${lua})

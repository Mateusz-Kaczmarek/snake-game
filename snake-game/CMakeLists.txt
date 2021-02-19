cmake_minimum_required(VERSION 3.5)

project(snake-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#allow you to use gdb
#set(CMAKE_BUILD_TYPE Debug)

#Bring the headers
include_directories(inc)

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)

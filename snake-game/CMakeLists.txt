cmake_minimum_required(VERSION 3.5)

project(snake-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Bring the headers, such as Student.h into the project
include_directories(inc)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allow
file(GLOB SOURCES "src/*.cpp")

add_executable(snake-game ${SOURCES})

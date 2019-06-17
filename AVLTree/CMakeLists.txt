cmake_minimum_required(VERSION 2.8)

project(AVLTree)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
set(CMAKE_CXX_FLAGS -pthread)
add_definitions(-std=c++11)

ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


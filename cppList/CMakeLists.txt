cmake_minimum_required(VERSION 2.8)

project(cppList)
#add_executable(${PROJECT_NAME} "main.cc")
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
set(CMAKE_CXX_FLAGS -pthread)

ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})


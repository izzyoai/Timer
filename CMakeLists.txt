cmake_minimum_required (VERSION 3.8)

project ("demo")

#c++ standard
set(CMAKE_CXX_STANDARD 17)

#set HOME dir
set(HOME ${PROJECT_SOURCE_DIR})

#set static library directory
set(STATIC_LIB ${HOME}/lib)

#set shared library directory
set(SHARED_LIB ${HOME}/bin)

#executable output path
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)

message(STATUS "executable path "${})

#set header directory
set(HEADER ${HOME}/src)

message(STATUS "header path "${HEADER})

#set project name
set(APP demo)

#subdirectory
add_subdirectory(${HOME}/src)

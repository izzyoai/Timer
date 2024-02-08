cmake_minimum_required (VERSION 3.8)

project ("timer")

#output static library
set(LIBRARY_OUTPUT_PATH ${STATIC_LIB})

add_library(timer STATIC timer.cpp)



cmake_minimum_required (VERSION 3.8)

project ("main")

include_directories(${HEADER})

#Visual Studio project
message(STATUS "the project is "${CMAKE_GENERATOR})
if (${CMAKE_GENERATOR} MATCHES "Visual Studio*")

#Release project
if(CMAKE_BUILD_TYPE STREQUAL "Release")

message(STATUS "library path "${STATIC_LIB}/Release/)
link_libraries(${STATIC_LIB}/Release/timer.lib)

#additionally,it is generally Debug ,if it's something else,configuration name
else()

message(STATUS "library path "${STATIC_LIB}/Debug/)
link_libraries(${STATIC_LIB}/Debug/timer.lib)

endif()

else()
#linux thread
set(CMAKE_CXX_FLAGS -lpthread)
message(STATUS "library path "${STATIC_LIB})
link_libraries(${STATIC_LIB}/libtimer.a)

endif()

add_executable(${APP}  "main.cpp")





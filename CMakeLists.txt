cmake_minimum_required(VERSION 3.15)
project(TIMER)
include_directories(${PROJECT_SOURCE_DIR}/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC)
#linux g++ 编译需要以下指令 -lpthread
set(CMAKE_CXX_FLAGS -lpthread)
add_executable(app ${SRC})
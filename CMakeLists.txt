cmake_minimum_required(VERSION 2.8)
project(game_server)

add_compile_options(-std=c++11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -g -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++11 -g -O0")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(./src/conn/ CONN_DIR_SRCS)
add_library(conn SHARED ${CONN_DIR_SRCS})

add_executable(echoserver task/echo_server/echoserver.cpp)
target_link_libraries(echoserver conn)
add_executable(echoclient task/echo_server/echoclient.cpp)

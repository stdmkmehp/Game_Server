cmake_minimum_required(VERSION 2.8)
project(game_server)

add_compile_options(-std=c++11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -g -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c++11 -g -O0")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(Protobuf)
if(PROTOBUF_FOUND)
    message(STATUS "found protobuf")
endif()

aux_source_directory(./src/conn/ CONN_DIR_SRCS)
add_library(conn SHARED ${CONN_DIR_SRCS})

#-------------------------------------------------------------------
# echo server
add_executable(echoserver task/echo_server/echoserver.cpp)
target_link_libraries(echoserver conn)
add_executable(echoclient task/echo_server/echoclient.cpp)

#-------------------------------------------------------------------
# protobuf_msg
add_library(msg_pb3 task/protobuf_msg/msg_pb3.pb.cc)
target_link_libraries(msg_pb3 protobuf pthread)

add_executable(protobuf_client task/protobuf_msg/protobuf_client.cpp)
target_link_libraries(protobuf_client msg_pb3 conn)

add_executable(protobuf_server task/protobuf_msg/protobuf_server.cpp)
target_link_libraries(protobuf_server msg_pb3 conn)

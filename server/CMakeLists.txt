cmake_minimum_required(VERSION 3.10)
project(tcp_chat_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -std=c++17")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

link_directories(../chatillo)
link_libraries(chatillo)

#server
set(SERVER_SRC
        src/main.cpp)

add_executable(server ${SERVER_SRC})
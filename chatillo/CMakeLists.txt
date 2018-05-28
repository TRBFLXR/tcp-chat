cmake_minimum_required(VERSION 3.10)
project(chatillo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

find_package(Threads REQUIRED)

include_directories(include)

#chatillo
set(CHATILLO_SRC
        src/packet.cpp
        src/packetmanager.cpp
        src/packetstructure.cpp
        src/socket.cpp)

add_library(chatillo SHARED ${CHATILLO_SRC})
target_link_libraries(chatillo Threads::Threads ws2_32)
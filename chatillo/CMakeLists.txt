cmake_minimum_required(VERSION 3.10)
project(chatillo)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

find_package(Threads REQUIRED)

#chatillo
set(CHATILLO_SRC
        src/packet.cpp)

add_library(chatillo SHARED ${CHATILLO_SRC})
target_link_libraries(chatillo Threads::Threads ws2_32)
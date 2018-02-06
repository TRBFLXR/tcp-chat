cmake_minimum_required(VERSION 3.10)
project(tcp_chat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -std=c++17")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

add_definitions(-DUNICODE)

find_package(Threads REQUIRED)

#client
set(CLIENT_SRC
        src/client/main.cpp
        src/client/ui/window.cpp
        src/client/ui/components/button.cpp )

#win32
add_executable(client_win32 WIN32 ${CLIENT_SRC})

target_link_libraries(client_win32
        Threads::Threads
        ws2_32)

#console sub
add_executable(client ${CLIENT_SRC})

target_link_libraries(client
        Threads::Threads
        ws2_32)

#server
set(SERVER_SRC
        src/server/main.cpp)

add_executable(server ${SERVER_SRC})

target_link_libraries(server
        Threads::Threads
        ws2_32)
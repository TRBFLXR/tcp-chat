cmake_minimum_required(VERSION 3.10)
project(tcp_chat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -std=c++17")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

add_definitions(-DUNICODE)

find_package(Threads REQUIRED)

#chatillo
set(CHATILLO_SRC
        src/chatillo/test.cpp)

add_library(chatillo SHARED ${CHATILLO_SRC})

target_link_libraries(chatillo Threads::Threads)

#client
set(CLIENT_SRC
        src/client/main.cpp
        src/client/ui/window.cpp
        src/client/ui/components/button.cpp
        src/client/ui/components/components.cpp
        src/client/ui/components/textfield.cpp
        src/client/ui/components/textarea.cpp)

#win32
add_executable(client_win32 WIN32 ${CLIENT_SRC})

target_link_libraries(client_win32
        chatillo
        ws2_32)

#console sub
add_executable(client ${CLIENT_SRC})

target_link_libraries(client
        chatillo
        ws2_32)

#server
set(SERVER_SRC
        src/server/main.cpp src/chatillo/test.hpp)

add_executable(server ${SERVER_SRC})

target_link_libraries(server
        chatillo
        ws2_32)
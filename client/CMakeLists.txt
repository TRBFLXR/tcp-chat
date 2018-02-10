cmake_minimum_required(VERSION 3.10)
project(tcp_chat_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++ -std=c++17")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")

add_definitions(-DUNICODE)

include_directories(../chatillo/include)
link_libraries(chatillo)

#client
set(CLIENT_SRC
        src/client.cpp
        src/main.cpp
        src/ui/window.cpp
        src/ui/components.cpp
        src/ui/components/button.cpp
        src/ui/components/textfield.cpp
        src/ui/components/textarea.cpp
        src/ui/mainwindow/mainwindow.cpp
        src/ui/mainwindow/mainwindowcomponents.cpp
        src/ui/configwindow/configwindow.cpp
        src/ui/configwindow/configwindowcomponents.cpp
        src/application.cpp
        src/config.cpp)

#win32
add_executable(client_win32 WIN32 ${CLIENT_SRC})

#console sub
add_executable(client ${CLIENT_SRC})
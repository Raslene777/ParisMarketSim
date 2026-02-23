cmake_minimum_required(VERSION 3.21)
project(ServeurBoursier)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(ServeurBoursier
        include/gui/LoginWindow.hpp
        src/gui/LoginWindow.cpp)

target_sources(ServeurBoursier PRIVATE

        # MAIN
        src/main/main.cpp

        # CORE
        src/core/Ordre.cpp
        src/core/Transaction.cpp

        # ENGINE
        src/engine/MatchingEngine.cpp

        # SYSTEM
        src/system/Serveur.cpp
        src/system/Interface.cpp

        # USER
        src/user/Client.cpp
        src/user/Portefeuille.cpp

        # GUI
        src/gui/DashboardWindow.cpp
        include/gui/DashboardWindow.hpp
)

target_include_directories(ServeurBoursier PRIVATE include)

target_link_libraries(ServeurBoursier PRIVATE Qt6::Widgets)
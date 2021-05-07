cmake_minimum_required(VERSION 3.13)
project(GravitySimulation)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR "/home/michal/Libraries/SFML-2.5.1-co/include")
set(SFML_LIBRARY_DIR "/home/michal/Libraries/SFML-2.5.1/lib")
set(SFML_DIR "/home/michal/Libraries/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(GravitySimulation src/main.cpp src/Game.cpp src/Game.h src/Game.cpp src/Game.h src/Player.cpp src/Player.h src/Ball.cpp src/Ball.h)
target_link_libraries (GravitySimulation sfml-graphics sfml-window sfml-system)
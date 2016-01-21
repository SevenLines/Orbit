#cmake_minimum_required(VERSION 3.3)
#project(orbit2)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#
#set(SOURCE_FILES main.cpp)
#include_directories(3rdparty/oxygine-framework/oxygine)
#add_executable(orbit2 ${SOURCE_FILES})

cmake_minimum_required (VERSION 3.2)
project (orbit2)

find_package(Boost)

add_subdirectory(3rdparty/oxygine-framework/ oxygine-framework)
add_subdirectory(3rdparty/oxygine-sound/ oxygine-sound)
add_definitions(${OXYGINE_DEFINITIONS})

include_directories(${OXYGINE_INCLUDE_DIRS})
include_directories(3rdparty/nanovg/src)

link_directories(${OXYGINE_LIBRARY_DIRS})

link_directories(libs/linux64/)
link_libraries(GL GLU m GLEW)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(orbit2 src/main.cpp src/game.cpp
        src/game.h src/Actors/Space.cpp
        src/Actors/Space.h src/Actors/Planet.cpp
        src/Actors/Planet.h src/Actors/Rocket.cpp
        src/Actors/Rocket.h src/Actors/Player.cpp
        src/Actors/Player.h src/Actors/GlobalState.cpp
        src/Actors/GlobalState.h
        3rdparty/nanovg/src/nanovg.c
        src/Actors/Anchor.cpp src/Actors/Anchor.h src/Actors/Way.cpp src/Actors/Way.h src/Helpers/Format.cpp src/Helpers/Format.h src/Actors/Body.cpp src/Actors/Body.h src/Helpers/types.cpp src/Helpers/types.h)

if (WIN32) #disable console mode for VC++
    set_target_properties(orbit2 PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

target_link_libraries(orbit2 ${OXYGINE_CORE_LIBS})
cmake_minimum_required(VERSION 3.14)
project(498735-nam-2023)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SFML_INCLUDE_DIR "./SFML/include")
set(SFML_LIBRARY_DIR "./SFML/build/lib")
set(CMAKE_BUILD_TYPE Release)



link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)


set(SOURCE_FILES main.cpp)

add_executable(498735-nam-2023
        button.cpp
        button.hpp
        character.cpp
        character.hpp
        gameObject.cpp
        gameObject.hpp
        main.cpp
        scene.cpp
        scene.hpp
        sceneHandler.cpp
        sceneHandler.hpp
        spriteObject.cpp
        spriteObject.hpp
        textObject.cpp
        textObject.hpp)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(498735-nam-2023 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

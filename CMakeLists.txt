cmake_minimum_required(VERSION 3.12)
project(SFML_Template)

set(CMAKE_CXX_STANDARD 14)

include_directories("C:/mingw/include")
include_directories("C:/mingw64/include")
include_directories("C:/mingw64/mingw64/include")
include_directories("C:/mingw64/x86_64-w64-mingw32/include")

add_executable(SFML_Template main.cpp Asteroid.cpp Asteroid.h GameManager.cpp GameManager.h Player.cpp Player.h Missile.cpp Missile.h)

target_link_directories(SFML_Template PUBLIC "C:/mingw/lib")
target_link_directories(SFML_Template PUBLIC "C:/mingw64/lib")
target_link_directories(SFML_Template PUBLIC "C:/mingw64/mingw64/lib")
target_link_directories(SFML_Template PUBLIC "C:/mingw64/x86_64-w64-mingw32/lib")

target_link_libraries(SFML_Template sfml-graphics sfml-system sfml-window sfml-main)

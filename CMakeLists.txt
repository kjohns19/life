cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(GameOfLife)

set(SFML_BASE /home/kevin/SFML-2.1)

add_executable(life src/main.cpp src/Grid.cpp src/GridDisplayTerm.cpp src/StateMachine.cpp src/StatePalette.cpp src/GridDisplay.cpp)
target_link_libraries(life sfml-window sfml-system sfml-graphics)

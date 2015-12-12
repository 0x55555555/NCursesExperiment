cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

add_executable(ncurses_experiment
  main.cpp
)

add_definitions(-std=c++1z)

target_link_libraries(ncurses_experiment
  PRIVATE
    ncurses)

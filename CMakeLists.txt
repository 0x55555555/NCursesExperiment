cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

add_executable(ncurses_experiment
  main.cpp

  src/ncurses/Context.h
  src/ncurses/Object.h
  src/ncurses/Painter.h
  src/ncurses/Position.h
  src/ncurses/RefreshBlock.h
  src/ncurses/Window.h
)

add_definitions(-std=c++1z)

target_include_directories(ncurses_experiment
  PRIVATE
    src
)

target_link_libraries(ncurses_experiment
  PRIVATE
    panel
    ncurses
)

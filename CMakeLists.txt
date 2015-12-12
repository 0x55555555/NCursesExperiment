cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

add_executable(ncurses_experiment
  main.cpp

  src/ncurses/Context.h
  src/ncurses/Object.h
  src/ncurses/Painter.h
  src/ncurses/Panel.h
  src/ncurses/Position.h
  src/ncurses/RefreshBlock.h
  src/ncurses/Window.h
)

target_include_directories(ncurses_experiment
  PRIVATE
    src
)

if (WIN32)
  option(PD_CURSES_DIR "")
  message("Using pdcurses from ${PD_CURSES_DIR}")
  target_link_libraries(ncurses_experiment
    PRIVATE
      ${PD_CURSES_DIR}\\win32\\panel.lib
      ${PD_CURSES_DIR}\\win32\\pdcurses.lib
  )

  target_include_directories(ncurses_experiment
    PRIVATE
      ${PD_CURSES_DIR}
  )
else()
  target_link_libraries(ncurses_experiment
    PRIVATE
      panel
      ncurses
  )

  add_definitions(-std=c++1z)
endif()

#pragma once
#include "ncurses/Panel.h"
#include "ncurses/Window.h"

#include <memory>

namespace ncurses
{

class Context
{
public:
  enum class Cursor
  {
    Invisible = 0,
    Normal = 1,
    HighVisibility = 2
  };

  void enable_echo(bool enable)
  {
    if (enable)
    {
      echo();
    }
    else
    {
      noecho();
    }
  }

  void set_cursor_mode(Cursor c)
  {
    curs_set((int)c);
  }

  Context()
  {
    // Start curses mode
    ::initscr();
  }

  ~Context()
  {
    // Restore normal terminal behavior
    ::endwin();
  }

  std::unique_ptr<Window> main_window()
  {
    return std::make_unique<Window>(stdscr, false);
  }

  std::unique_ptr<Panel> new_panel(Position position, Size size)
  {
    return std::make_unique<Panel>(newwin(size.y(), size.x(), position.y(), position.x()), true);
  }

  void update_panels()
  {
    ::update_panels();
    ::doupdate();
  }
};

}

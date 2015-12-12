#pragma once
#include "ncurses/Position.h"
#include "ncurses/Painter.h"

#include <cstddef>
#include <vector>
#ifdef _WIN32
# include <curses.h>
#else
# include <ncurses.h>
#endif
#include <memory>
#include <panel.h>

namespace ncurses
{

/// Window containing all ncurses interactions
class Window : public Painter
{
public:
  Window(WINDOW *w, bool delete_window)
  {
    _screen = w;
    if (!_screen) {
      throw std::logic_error("Invalid window passed");
    }

    delete_window = delete_window;

    box(_screen, '1', '2');

    clear();
  }

  ~Window()
  {
    if (_delete_window)
    {
      delwin(_screen);
    }
  }

  Size size()
  {
    int x, y;
    getmaxyx(_screen, y, x);
    return { x, y };
  }

  void resize(Size s)
  {
    wresize(_screen, s.y(), s.x());
  }

  Position position()
  {
    int x, y;
    getbegyx(_screen, y, x);
    return { x, y };
  }

  void move_to(Position p)
  {
    mvwin(_screen, p.y(), p.x());
  }

  void clear()
  {
    ::werase(_screen);
  }

  using Painter::print;
  void print(Position pos, const char *data, std::size_t len) override
  {
    mvwaddnstr(_screen, pos.y(), pos.x(), data, (int)len);
  }

  void push_refresh_block()
  {
    ++refresh_block_count;
  }

  void pop_refresh_block()
  {
    --refresh_block_count;
    refresh();
  }

  void refresh()
  {
    if (refresh_block_count == 0)
    {
      //::wrefresh(_screen);
	  ::wnoutrefresh(_screen);
    }
  }

  std::unique_ptr<Window> sub_window(Position pos, Size size)
  {
    auto new_win = derwin(_screen, size.y(), size.x(), pos.y(), pos.x());
    return std::make_unique<Window>(new_win, true);
  }

protected:
  WINDOW *_screen = nullptr;
  bool _delete_window = false;
  std::size_t refresh_block_count = 0;

  friend class Context;
};

}

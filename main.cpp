#include <cstdint>
#include <cstddef>
#include <ncurses.h>

#define DELAY 30000

namespace ncurses
{

using ScreenScalar = int;

/// A position in the window
class Position
{
public:
  Position()
  : _x(0), _y(0)
  {
  }

  Position(ScreenScalar x, ScreenScalar y)
  : _x(x), _y(y)
  {
  }

  ScreenScalar x() const { return _x; }
  ScreenScalar y() const { return _y; }

private:
  ScreenScalar _x;
  ScreenScalar _y;
};

using Size = Position;

/// A persistent object in the window
class Object
{
public:
  Object()
  {
  }

  void set_position(const Position &p)
  {
    position = p;
  }

  void set_size(const Position &s)
  {
    size = s;
  }

private:
  Position position;
  Size size;
};

/// Window containing all ncurses interactions
class Window
{
public:
  enum class Cursor
  {
    Invisible = 0,
    Normal = 1,
    HighVisibility = 2
  };

  ~Window()
  {
  }

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

  Position current()
  {
    int x, y;
    getmaxyx(_screen, x, y);
    return { x, y };
  }

  void clear()
  {
    ::clear();
  }

  void print(ScreenScalar x, ScreenScalar y, const char *data)
  {
    ::mvprintw(y, x, data);
  }

  void print(Position pos, const char *data)
  {
    print(pos.x(), pos.y(), data);
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
      ::refresh();
    }
  }

private:
  Window(WINDOW *w)
  {
    _screen = w;

    clear();
  }

  WINDOW *_screen = nullptr;
  std::size_t refresh_block_count = 0;
  friend class Context;
};

/// Block all refreshes to window until all blocks are terminated
class RefreshBlock
{
public:
  RefreshBlock(Window &w)
  : RefreshBlock(&w)
  {
  }

  RefreshBlock(Window *w)
  : window(w)
  {
    window->push_refresh_block();
  }

  ~RefreshBlock()
  {
    window->pop_refresh_block();
  }

  Window *window;
};

class Context
{
public:
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

  Window main_window()
  {
    return Window(stdscr);
  }
};

}

int main(int argc, char *argv[])
{
  ncurses::Context c;
  auto w = c.main_window();
  w.enable_echo(false);
  w.set_cursor_mode(ncurses::Window::Cursor::Invisible);

  int x = 0, y = 0;
  while(1) {
    ncurses::RefreshBlock b(w);
    w.clear();

    w.print({x, y}, "o");  // Print our "ball" at the current xy position

    usleep(DELAY);       // Shorter delay between movements
    x++;                 // Advance the ball to the right
  }

  sleep(1);


}

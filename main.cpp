#include "ncurses/Context.h"
#include "ncurses/RefreshBlock.h"

#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
  ncurses::Context c;
  auto w = c.main_window();
  c.enable_echo(false);
  c.set_cursor_mode(ncurses::Context::Cursor::Invisible);

  auto size = w->size();

  auto sub = c.new_panel(ncurses::Position(10, 10), ncurses::Size(50, 50));

  int x = 0, y = 0;
  while(true) {
    auto size = w->size();
    w->clear();

    w->print({x, y}, "o");  // Print our "ball" at the current xy position
    sub->print({0, 0}, "POSRK");

    std::this_thread::sleep_for(std::chrono::microseconds(30000));       // Shorter delay between movements
    x++;                 // Advance the ball to the right
    if (x == size.x()) {
      x = 0;
      ++y;
    }
    
    c.update_panels();
  }

  sleep(1);
}

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


  auto bottom = c.new_panel(ncurses::Position(0, size.y()-5), ncurses::Size(size.x(), 5));

  auto bottom_sub = bottom->sub_window(ncurses::Position(1, 1), ncurses::Size(20, 3));
  bottom_sub->print({ 0, 0 }, "test");
  bottom->border();

  auto sub = c.new_panel(ncurses::Position(10, 10), ncurses::Size(10, 10));
  sub->border();
  sub->print({ 1, 1 }, "POSRK");

  auto sub2 = c.new_panel(ncurses::Position(19, 6), ncurses::Size(10, 10));
  sub2->border();
  sub2->print({ 1, 1 }, "POSRK2");

  auto sub3 = c.new_panel(ncurses::Position(29, 8), ncurses::Size(10, 10));
  sub3->border();
  sub3->print({ 1, 1 }, "POSRK3");

  int x = 0, y = 0;
  while(true) {
    {
      auto size = w->size();
      w->clear();

      sub->move_to({ 10 + x / 3, 10 });
      sub2->move_to({ 19 + x / 2, 6 });
      sub3->move_to({ 29 - x / 3, 8 });

      w->print({ x, y }, "o");  // Print our "ball" at the current xy position
      sub->show();
      sub2->show();
      sub3->show();


      std::this_thread::sleep_for(std::chrono::microseconds(30000));       // Shorter delay between movements
      x++;                 // Advance the ball to the right
      if (x == size.x()) {
        x = 0;
        ++y;
      }
    }
    
    c.update_panels();
  }
}

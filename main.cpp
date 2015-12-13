#include "ncurses/Context.h"
#include "ncurses/RefreshBlock.h"
#include "ncurses/TextBox.h"
#include "ncurses/HorizontalSlider.h"

#include <iostream>
#include <cmath>
#include <thread>


int main(int argc, char *argv[])
{
  ncurses::Context c;
  auto w = c.main_window();
  c.enable_echo(false);
  c.set_cursor_mode(ncurses::Context::Cursor::Invisible);

  auto size = w->size();


  auto bottom = c.new_panel(ncurses::Position(0, size.y()-5), ncurses::Size(size.x(), 5));

  auto bottom_sub = bottom->sub_window(ncurses::Position(1, 1), ncurses::Size(bottom->size().x()-2, 3));
  bottom_sub->print({ 0, 0 }, "test");
  bottom->draw_border();

  auto sub = c.new_panel(ncurses::Position(10, 10), ncurses::Size(10, 10));
  sub->draw_border();
  sub->print({ 1, 1 }, "POSRK");

  auto sub2 = c.new_panel(ncurses::Position(19, 6), ncurses::Size(10, 10));
  sub2->draw_border();
  sub2->print({ 1, 1 }, "POSRK2");

  auto sub3 = c.new_panel(ncurses::Position(29, 8), ncurses::Size(10, 10));
  sub3->draw_border();
  sub3->print({ 1, 1 }, "POSRK3");

  ncurses::TextBox text;
  ncurses::HorizontalSlider slider_x(0, 100, 50);
  ncurses::HorizontalSlider slider_y(0, 100, 50);

  int x = 0, y = 0;
  while(true) {
    {
      auto size = w->size();
      w->clear();

      sub->move_to({ 10 + x / 3, 10 });
      sub2->move_to({ 19 + x / 2, 6 });
      sub3->move_to({ 29 - x / 3, 8 });

      w->print({ x, y }, "o");  // Print our "ball" at the current xy position
      //sub->show();
      //sub2->show();
      //sub3->show();

      text.set_text(std::to_string(sin(float(x)/50) * 10));
      text.paint(bottom_sub.get(), ncurses::Rectangle({ bottom_sub->size().x()-15, 1 }, { 15, 1 }));

      slider_x.set_value(x);
      slider_y.set_value(sin(float(float(x)/25)) * 10);
      slider_x.paint(bottom_sub.get(), ncurses::Rectangle({ 0, 1 }, { bottom_sub->size().x()-16, 1 }));
      slider_y.paint(bottom_sub.get(), ncurses::Rectangle({ 0, 2 }, { bottom_sub->size().x()-16, 1 }));

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

#pragma once
#include "ncurses/Window.h"

#include <panel.h>

namespace ncurses
{

class Panel : public Window
{
public:
  Panel(WINDOW *w, bool delete_window)
  : Window(w, delete_window)
  {
    _panel = new_panel(_screen);
    show();
  }

  ~Panel()
  {
    del_panel(_panel);
  }

  void show()
  {
    show_panel(_panel);
  }

  void hide()
  {
    hide_panel(_panel);
  }


private:
  PANEL *_panel;
};

}

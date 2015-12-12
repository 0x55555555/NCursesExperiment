#pragma once
#include "ncurses/Window.h"

#include <memory>

namespace ncurses
{

/// Block all refreshes to window until all blocks are terminated
class RefreshBlock
{
public:
  RefreshBlock(const std::unique_ptr<Window> &w)
  : window(w.get())
  {
    window->push_refresh_block();
  }

  RefreshBlock(const std::unique_ptr<Panel> &w)
  : window(w.get())
  {
    window->push_refresh_block();
  }

  ~RefreshBlock()
  {
    window->pop_refresh_block();
  }

  Window *window;
};

}

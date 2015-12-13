#pragma once
#include "ncurses/Painter.h"

#include <string>

namespace ncurses
{

class TextBox
{
public:
  void paint(Painter *painter, Rectangle rect)
  {
    if (text.size() > rect.size().x())
    {
      painter->clear(rect, '?');
    }
    else
    {
      painter->clear(rect);
      painter->print(rect.position(), text.data(), rect.size().x());
    }
  }

  void set_text(const std::string &t)
  {
    text = t;
  }

private:
  std::string text;
};

}

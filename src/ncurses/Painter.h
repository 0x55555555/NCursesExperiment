#pragma once
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include "ncurses/Rectangle.h"

namespace ncurses
{

class Painter
{
public:
  virtual ~Painter()
  {
  }

  virtual void print(Position pos, const char *data, std::size_t len) = 0;

  void print(Position pos, const char *data)
  {
    print(pos, data, strlen(data));
  }

  void print(ScreenScalar x, ScreenScalar y, const char *data)
  {
    print({ x, y }, data);
  }

  void clear(Rectangle r, char clear_char = ' ')
  {
    std::array<char, 32> empty;
    std::fill(empty.begin(), empty.end(), clear_char);

    for (ScreenScalar y = 0; y < r.size().y(); ++y)
    {
      auto total = r.size().x();
      for (ScreenScalar x = 0; x < r.size().x(); x += empty.size())
      {
        auto len = std::min(empty.size(), std::size_t(total - x));
        print(r.position() + Position{ x, y }, empty.data(), len);
      }
    }
  }
};

}

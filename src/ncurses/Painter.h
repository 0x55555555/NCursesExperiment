#pragma once
#include <cstddef>
#include <cstring>

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
};

}

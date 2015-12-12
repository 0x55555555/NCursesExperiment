#pragma once
#include <cstdint>

namespace ncurses
{

using ScreenScalar = std::int32_t;

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

  Position operator+(Position oth) const
  {
    return { x() + oth.x(), y() + oth.y() };
  }

private:
  ScreenScalar _x;
  ScreenScalar _y;
};

using Size = Position;

}

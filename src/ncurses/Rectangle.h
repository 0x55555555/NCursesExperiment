#pragma once
#include "ncurses/Position.h"

namespace ncurses
{

class Rectangle
{
public:
  Rectangle()
  {
  }

  Rectangle(Position pos, Size size)
  : _pos(pos), _size(size)
  {
  }

  Position position() const { return _pos; }
  Size size() const { return _size; }

private:
  Position _pos;
  Size _size;
};

using Size = Position;

}

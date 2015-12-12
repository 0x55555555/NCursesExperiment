#pragma once
#include "ncurses/Painter.h"
#include "ncurses/Position.h"
#include "ncurses/Window.h"

#include <functional>
#include <stdexcept>

namespace ncurses
{

/// A persistent object in the window
class Object : public Paintable
{
public:
  using Paint = std::function<void(ncurses::Object &o, Painter *)>;

  enum class Border
  {
    None,
    Solid
  };

  Object(
    Window *w,
    const Position &p,
    const Size &s,
    Border b,
    const Paint &paint)
  : _window(w)
  , _border(b)
  , _paint(paint)
  {
    set_position(p);
    set_size(s);

    if (!_window)
    {
      throw std::logic_error("Invalid window");
    }

    _window->add_paintable(this);
  }

  ~Object()
  {
    _window->remove_paintable(this);
  }

  void set_position(const Position &p)
  {
    _position = p;
  }

  void set_size(const Position &s)
  {
    _size = s;
  }

  void paint(Painter *fwd) override
  {
    struct PainterWrapper : public Painter
    {
      void print(Position pos, const char *data, std::size_t length) override
      {
        fwd->print(pos + obj->_position, data, length);
      }

      Position offset;
      Painter *fwd;
    } painter;
    painter.offset = _position;
    painter.fwd = fwd;

    _paint(*this, &painter);
  }

private:
  Position _position;
  Size _size;
  Window *_window;
  Border _border;
  Paint _paint;
};

}

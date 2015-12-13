#pragma once
#include "ncurses/Painter.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace ncurses
{

class HorizontalSlider
{
public:
  HorizontalSlider(std::int64_t min, std::int64_t max, std::size_t history_count = 0)
  : value(0)
  , min(min)
  , max(max)
  , history_count(history_count)
  {
  }

  void paint(Painter *painter, Rectangle rect)
  {
    painter->clear(rect);
    render_point(painter, rect, '|', value);

    for (std::size_t i = 0; i < history.size(); ++i)
    {
      auto v = history[i];
      char chr = i > history.size()/2 ? '-' : '=';
      if (v != value)
      {
        render_point(painter, rect, chr, v);
      }
    }
  }

  void set_value(std::int64_t v)
  {
    history.insert(history.begin(), value);
    if (history.size() > history_count) {
      history.resize(history_count);
    }

    value = v;
  }

  ScreenScalar resolve(std::int64_t value, Rectangle rect) const
  {
    float ratio = double(value - min) / double(max - min);
    ScreenScalar sc = ratio * (rect.size().x()-1);

    return sc;
  }

private:
  void render_point(Painter *painter, Rectangle rect, char pt, std::int64_t value) const
  {
    if (value > max || value < min)
    {
      return;
    }

    ScreenScalar position = resolve(value, rect);

    painter->print(rect.position() + Position{ position, 0 }, &pt, 1);
  }

  std::int64_t value;
  std::int64_t min;
  std::int64_t max;
  std::vector<std::int64_t> history;
  std::size_t history_count;
};

}

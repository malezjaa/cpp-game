#ifndef INC_2D_GAME_MENU_H
#define INC_2D_GAME_MENU_H

#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "TextRenderer.h"

class Menu {
public:
  struct Option {
    std::string text;
    std::function<void()> action;
  };

  explicit Menu(std::vector<Option> options) : options(std::move(options)) {}

  void Draw(const TextRenderer &text_renderer, float scale, Color text_color, Color hovered_text_color) const;

private:
  std::vector<Option> options;
};

#endif

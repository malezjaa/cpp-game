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

  void Draw(const TextRenderer &text_renderer, const float scale, const Color text_color,
            const Color hovered_text_color) const {
    constexpr std::string_view title = "paradigm";
    constexpr float title_size = 28.0f;
    constexpr float option_size = 23.0f;
    constexpr float option_gap = 20.0f;
    const auto screen_height = static_cast<float>(GetScreenHeight());
    const float scaled_title_size = title_size * scale;
    const float scaled_option_size = option_size * scale;
    float x = 20.0f * scale;

    text_renderer.Render(std::string{title}, {x, screen_height - 50.0f * scale}, scaled_title_size, GRAY);
    x += text_renderer.Measure(std::string{title}, scaled_title_size).x + 40.0f * scale;

    const float option_y = screen_height - 45.0f * scale;
    for (const Option &option: options) {
      const Vector2 text_size = text_renderer.Measure(option.text, scaled_option_size);
      const Rectangle bounds{x, option_y, text_size.x, text_size.y};
      const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);

      text_renderer.Render(option.text, {x, option_y}, scaled_option_size, hovered ? hovered_text_color : text_color);

      if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        option.action();
      }

      x += bounds.width + option_gap * scale;
    }
  }

private:
  std::vector<Option> options;
};

#endif

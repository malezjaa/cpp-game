#ifndef INC_2D_GAME_DIALOG_H
#define INC_2D_GAME_DIALOG_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "../Textures.h"
#include "Panel.h"
#include "TextRenderer.h"

class Dialog {
public:
  struct Button {
    std::string text;
    std::function<void()> action;
    std::optional<Rectangle> icon;
  };

  explicit Dialog(std::string message, std::optional<std::string> title = std::nullopt,
                  std::vector<Button> buttons = {}) :
      title(std::move(title)), message(std::move(message)), buttons(std::move(buttons)) {
    if (this->buttons.empty()) {
      this->buttons.push_back({"OK", {}});
    }
  }

  [[nodiscard]] std::optional<std::size_t> Draw(const TextRenderer &text, const Textures &textures, const float scale,
                                                const Color text_color, const Color hovered_text_color) const {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 150});

    constexpr float dialog_width = 360.0f;
    constexpr float horizontal_padding = 24.0f;
    constexpr float vertical_padding = 20.0f;
    constexpr float title_size = 18.0f;
    constexpr float message_size = 12.0f;
    constexpr float button_size = 14.0f;
    constexpr float button_gap = 20.0f;
    constexpr float icon_gap = 6.0f;

    const float scaled_title_size = title_size * scale;
    const float scaled_message_size = message_size * scale;
    const float scaled_button_size = button_size * scale;
    const float scaled_padding_x = horizontal_padding * scale;
    const float scaled_padding_y = vertical_padding * scale;
    const float button_y_gap = 18.0f * scale;

    float content_height = text.Measure(message, scaled_message_size).y;
    if (title.has_value()) {
      content_height += text.Measure(*title, scaled_title_size).y + 12.0f * scale;
    }
    float button_height = 0.0f;
    for (const Button &button: buttons) {
      button_height = std::max(button_height, text.Measure(button.text, scaled_button_size).y);
      if (button.icon.has_value()) {
        button_height = std::max(button_height, button.icon->height * scale);
      }
    }
    content_height += button_y_gap + button_height;

    const float width = dialog_width * scale;
    const float height = content_height + scaled_padding_y * 2.0f;
    const Rectangle box{
        (static_cast<float>(GetScreenWidth()) - width) / 2.0f,
        (static_cast<float>(GetScreenHeight()) - height) / 2.0f,
        width,
        height,
    };
    Panel::Draw(textures.UI(), Textures::DIALOG_BORDER_RECT, box, {10.0f, 10.0f, 10.0f, 10.0f}, {69, 53, 68, 255},
                {37, 42, 56, 255});

    float y = box.y + scaled_padding_y;
    if (title.has_value()) {
      text.Render(*title, {box.x + scaled_padding_x, y}, scaled_title_size, hovered_text_color);
      y += text.Measure(*title, scaled_title_size).y + 12.0f * scale;
    }

    text.Render(message, {box.x + scaled_padding_x, y}, scaled_message_size, text_color);
    y += text.Measure(message, scaled_message_size).y + button_y_gap;

    float buttons_width = 0.0f;
    for (const Button &button: buttons) {
      buttons_width += text.Measure(button.text, scaled_button_size).x;
      if (button.icon.has_value()) {
        buttons_width += button.icon->width * scale + icon_gap * scale;
      }
    }
    buttons_width += button_gap * scale * static_cast<float>(buttons.size() - 1);

    float x = box.x + (box.width - buttons_width) / 2.0f;
    for (std::size_t index = 0; index < buttons.size(); ++index) {
      const Button &button = buttons[index];
      const Vector2 button_text_size = text.Measure(button.text, scaled_button_size);
      const float icon_width = button.icon.has_value() ? button.icon->width * scale + icon_gap * scale : 0.0f;
      const Rectangle bounds{x, y, icon_width + button_text_size.x, button_height};
      const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);

      if (button.icon.has_value()) {
        const Rectangle icon_destination{
            x,
            y + (button_text_size.y - button.icon->height * scale) / 2.0f,
            button.icon->width * scale,
            button.icon->height * scale,
        };
        DrawTexturePro(textures.UI2(), *button.icon, icon_destination, {}, 0.0f, WHITE);
      }

      text.Render(button.text, {x + icon_width, y}, scaled_button_size, hovered ? hovered_text_color : text_color);

      if (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return index;
      }

      x += bounds.width + button_gap * scale;
    }

    return std::nullopt;
  }

  void Trigger(const std::size_t index) const {
    if (const std::function<void()> &action = buttons.at(index).action; action) {
      action();
    }
  }

private:
  std::optional<std::string> title;
  std::string message;
  std::vector<Button> buttons;
};

#endif

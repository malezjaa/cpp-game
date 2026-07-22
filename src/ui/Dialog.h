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

  void Trigger(const std::size_t index) const {
    if (const std::function<void()> &action = buttons.at(index).action; action) {
      action();
    }
  }

  [[nodiscard]] std::optional<std::size_t> Draw(const TextRenderer &text, const Textures &textures, float scale,
                                                Color text_color, Color hovered_text_color) const;

private:
  std::optional<std::string> title;
  std::string message;
  std::vector<Button> buttons;
};

#endif

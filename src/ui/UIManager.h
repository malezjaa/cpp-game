#ifndef INC_2D_GAME_UIMANAGER_H
#define INC_2D_GAME_UIMANAGER_H
#include "../Textures.h"
#include "TextRenderer.h"


class UIManager {
public:
  static constexpr Color BACKGROUND_COLOR{31, 29, 29, 255};
  static constexpr Color TEXT_COLOR{130, 130, 130, 255};
  static constexpr Color HOVERED_TEXT_COLOR{230, 230, 230, 255};

  static constexpr float base_width = 800.0f;
  static constexpr float base_height = 450.0f;

  explicit UIManager(const Textures &textures) : text("../assets/fonts/BoldPixels.ttf"), textures(textures) {}

  [[nodiscard]] static float Scale() {
    const float scale_x = static_cast<float>(GetScreenWidth()) / base_width;
    const float scale_y = static_cast<float>(GetScreenHeight()) / base_height;

    return std::max(1.0f, std::floor(std::min(scale_x, scale_y)));
  }

  [[nodiscard]] bool TextButton(const std::string &label, const Vector2 position, const float font_size) const {
    const Rectangle bounds = text.Bounds(label, position, font_size);
    const bool hovered = CheckCollisionPointRec(GetMousePosition(), bounds);

    text.Render(label, position, font_size, hovered ? HOVERED_TEXT_COLOR : TEXT_COLOR);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  }

  [[nodiscard]] TextRenderer &Text() { return text; }

  [[nodiscard]] const TextRenderer &Text() const { return text; }

private:
  TextRenderer text;
  const Textures &textures;
};


#endif

#ifndef INC_2D_GAME_TEXTRENDERER_H
#define INC_2D_GAME_TEXTRENDERER_H
#include <Font.hpp>
class TextRenderer {
public:
  explicit TextRenderer(const char *path) : font(path) {}

  void Render(const std::string &text, const Vector2 position, const float size, const Color color = WHITE,
              const float spacing = 2.0f) const {
    font.DrawText(text.c_str(), position, size, spacing, color);
  }

  [[nodiscard]] Vector2 Measure(const std::string &text, const float size, const float spacing = 2.0f) const {
    return MeasureTextEx(font, text.c_str(), size, spacing);
  }

  [[nodiscard]] Rectangle Bounds(const std::string &text, const Vector2 position, const float size,
                                 const float spacing = 2.0f) const {
    const auto [x, y] = Measure(text, size, spacing);

    return {
        position.x,
        position.y,
        x,
        y,
    };
  }

private:
  raylib::Font font;
};

#endif

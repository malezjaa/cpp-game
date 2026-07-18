#ifndef INC_2D_GAME_TEXTRENDERER_H
#define INC_2D_GAME_TEXTRENDERER_H
#include <Font.hpp>

class TextRenderer {
public:
  explicit TextRenderer(const char *path) : font(raylib::Font(path)) {}

  void Render(const std::string &text, const Vector2 position, const float size, const Color color = WHITE) const {
    font.DrawText(text.c_str(), position, size, 2, color);
  }

private:
  raylib::Font font;
};

#endif

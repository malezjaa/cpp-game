#ifndef INC_2D_GAME_UIMANAGER_H
#define INC_2D_GAME_UIMANAGER_H
#include <vector>
#include "../Textures.h"
#include "NineSlice.h"
#include "TextRenderer.h"

enum class AlertLevel { Info, Warning, Error };

class UIManager {
public:
  static constexpr Color BACKGROUND_COLOR{31, 29, 29, 255};
  static constexpr Color TEXT_COLOR{130, 130, 130, 255};
  static constexpr Color HOVERED_TEXT_COLOR{230, 230, 230, 255};

  static constexpr float base_width = 800.0f;
  static constexpr float base_height = 450.0f;

  static constexpr float ALERT_SLIDE_DURATION = 0.35f;
  static constexpr float ALERT_WIDTH = 220.0f;
  static constexpr float ALERT_HEIGHT = 35.0f;
  static constexpr float ALERT_MARGIN = 14.0f;
  static constexpr float ALERT_SPACING = 8.0f;

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

  void Alert(const std::string &message, const AlertLevel level = AlertLevel::Info, const float duration = 3.0f) const {
    alerts.push_back({message, level, duration, GetTime()});
  }

  void DrawAlerts() const {
    const float scale = Scale();
    const auto screen_w = static_cast<float>(GetScreenWidth());
    float y = ALERT_MARGIN * scale;

    for (auto it = alerts.begin(); it != alerts.end();) {
      const double elapsed = GetTime() - it->start_time;

      if (const float total_duration = ALERT_SLIDE_DURATION * 2.0f + it->duration; elapsed >= total_duration) {
        it = alerts.erase(it);
        continue;
      }

      const float width = ALERT_WIDTH * scale;
      const float height = ALERT_HEIGHT * scale;

      float progress;

      if (elapsed < ALERT_SLIDE_DURATION) {
        progress = EaseOutCubic(static_cast<float>(elapsed) / ALERT_SLIDE_DURATION);
      } else if (elapsed < ALERT_SLIDE_DURATION + it->duration) {
        progress = 1.0f;
      } else {
        const float t = (static_cast<float>(elapsed) - ALERT_SLIDE_DURATION - it->duration) / ALERT_SLIDE_DURATION;

        progress = 1.0f - EaseOutCubic(t);
      }

      const float x = screen_w - progress * (width + ALERT_MARGIN * scale);

      const Rectangle box{x, y, width, height};

      NineSlice::Draw(textures.UI(), Textures::ALERT_BACKGROUND_RECT, box, {10.0f, 10.0f, 10.0f, 10.0f});

      constexpr float ALERT_FONT_SIZE = 10.0f;
      const float font_size = ALERT_FONT_SIZE * scale;
      const Vector2 text_size = text.Measure(it->message, font_size);
      constexpr float ALERT_ICON_WIDTH = 4.0f;
      constexpr float ALERT_ICON_HEIGHT = 10.0f;

      const Rectangle icon_rect{
          x + 10.0f * scale,
          y + (height - ALERT_ICON_HEIGHT * scale) / 2.0f,
          ALERT_ICON_WIDTH * scale,
          ALERT_ICON_HEIGHT * scale,
      };
      DrawTexturePro(textures.UI2(), LevelIconRect(it->level), icon_rect, {}, 0.0f, WHITE);

      const Vector2 text_pos{
          icon_rect.x + icon_rect.width + 8.0f * scale,
          y + (height - text_size.y) / 2.0f,
      };

      text.Render(it->message, text_pos, font_size);

      y += height + ALERT_SPACING * scale;
      ++it;
    }
  }

  [[nodiscard]] TextRenderer &Text() { return text; }
  [[nodiscard]] const TextRenderer &Text() const { return text; }

private:
  struct ActiveAlert {
    std::string message;
    AlertLevel level;
    float duration;
    double start_time;
  };

  [[nodiscard]] static float EaseOutCubic(const float t) {
    const float f = t - 1.0f;
    return f * f * f + 1.0f;
  }

  [[nodiscard]] static Rectangle LevelIconRect(const AlertLevel level) {
    switch (level) {
      case AlertLevel::Warning:
        return Textures::ALERT_WARNING_ICON_RECT;
      case AlertLevel::Error:
        return Textures::ALERT_ERROR_ICON_RECT;
      default:
        return Textures::ALERT_INFO_ICON_RECT;
    }
  }

  TextRenderer text;
  const Textures &textures;
  mutable std::vector<ActiveAlert> alerts;
};

#endif

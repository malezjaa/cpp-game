#include "Alert.h"

float AlertManager::SlideProgress(const float elapsed, const float display_duration) {
  if (elapsed < SLIDE_DURATION) {
    return EaseOutCubic(elapsed / SLIDE_DURATION);
  }

  if (elapsed < SLIDE_DURATION + display_duration) {
    return 1.0f;
  }

  return 1.0f - EaseOutCubic((elapsed - SLIDE_DURATION - display_duration) / SLIDE_DURATION);
}

float AlertManager::EaseOutCubic(const float t) {
  const float f = t - 1.0f;
  return f * f * f + 1.0f;
}

Rectangle AlertManager::LevelIconRect(const AlertLevel level) {
  switch (level) {
    case AlertLevel::Warning:
      return Textures::ALERT_WARNING_ICON_RECT;
    case AlertLevel::Error:
      return Textures::ALERT_ERROR_ICON_RECT;
    default:
      return Textures::ALERT_INFO_ICON_RECT;
  }
}

std::pair<Color, Color> AlertManager::ColorsFor(const AlertLevel level) {
  switch (level) {
    case AlertLevel::Warning:
      return {{93, 66, 43, 255}, {55, 39, 35, 255}};
    case AlertLevel::Error:
      return {{86, 47, 57, 255}, {55, 31, 43, 255}};
    default:
      return {{53, 67, 88, 255}, {32, 43, 60, 255}};
  }
}

void AlertManager::Draw(const TextRenderer &text, const Textures &textures, const float scale) {
  const auto screen_width = static_cast<float>(GetScreenWidth());
  float y = MARGIN * scale;

  for (auto it = active_alerts.begin(); it != active_alerts.end();) {
    const double elapsed = GetTime() - it->start_time;

    if (const float total_duration = SLIDE_DURATION * 2.0f + it->duration; elapsed >= total_duration) {
      it = active_alerts.erase(it);
      continue;
    }

    const float width = WIDTH * scale;
    const float height = HEIGHT * scale;
    const float progress = SlideProgress(static_cast<float>(elapsed), it->duration);
    const float x = screen_width - progress * (width + MARGIN * scale);
    const Rectangle box{x, y, width, height};

    const auto [top_color, bottom_color] = ColorsFor(it->level);
    Panel::Draw(textures.UI(), Textures::ALERT_BORDER_RECT, box, {8.0f, 5.0f, 8.0f, 5.0f}, top_color, bottom_color);

    constexpr float font_size = 10.0f;
    constexpr float icon_width = 4.0f;
    constexpr float icon_height = 10.0f;
    const Vector2 text_size = text.Measure(it->message, font_size * scale);
    const Rectangle icon_rect{
        x + 10.0f * scale,
        y + (height - icon_height * scale) / 2.0f,
        icon_width * scale,
        icon_height * scale,
    };

    DrawTexturePro(textures.UI2(), LevelIconRect(it->level), icon_rect, {}, 0.0f, WHITE);
    text.Render(it->message, {icon_rect.x + icon_rect.width + 8.0f * scale, y + (height - text_size.y) / 2.0f},
                font_size * scale);

    y += height + SPACING * scale;
    ++it;
  }
}

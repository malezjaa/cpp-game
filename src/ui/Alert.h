#ifndef INC_2D_GAME_ALERT_H
#define INC_2D_GAME_ALERT_H

#include <string>
#include <utility>
#include <vector>

#include "../Textures.h"
#include "Panel.h"
#include "TextRenderer.h"

enum class AlertLevel { Info, Warning, Error };

class AlertManager {
public:
  static constexpr float SLIDE_DURATION = 0.35f;
  static constexpr float WIDTH = 220.0f;
  static constexpr float HEIGHT = 35.0f;
  static constexpr float MARGIN = 14.0f;
  static constexpr float SPACING = 8.0f;

  void Show(std::string message, const AlertLevel level = AlertLevel::Info, const float duration = 3.0f) {
    active_alerts.push_back({std::move(message), level, duration, GetTime()});
  }

  void Draw(const TextRenderer &text, const Textures &textures, float scale);

private:
  struct ActiveAlert {
    std::string message;
    AlertLevel level;
    float duration;
    double start_time;
  };

  [[nodiscard]] static float SlideProgress(float elapsed, float display_duration);
  [[nodiscard]] static float EaseOutCubic(float t);
  [[nodiscard]] static Rectangle LevelIconRect(AlertLevel level);
  [[nodiscard]] static std::pair<Color, Color> ColorsFor(AlertLevel level);

  std::vector<ActiveAlert> active_alerts;
};

#endif

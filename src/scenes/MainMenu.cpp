#include "MainMenu.h"

#include <functional>

void MainMenu::Update() {}

void MainMenu::Draw() {
  ClearBackground(UIManager::BACKGROUND_COLOR);

  const float scale = UIManager::Scale();
  const auto screen_height = static_cast<float>(GetScreenHeight());

  float x = 20.0f * scale;

  constexpr std::string_view title = "paradigm";

  const float title_size = 28.0f * scale;
  const float option_size = 23.0f * scale;
  const float option_gap = 20.0f * scale;

  const Vector2 title_position{
      x,
      screen_height - 50.0f * scale,
  };

  scene_manager.UI().Text().Render(std::string{title}, title_position, title_size, GRAY);

  x += scene_manager.UI().Text().Measure(std::string{title}, title_size).x;
  x += 40.0f * scale;

  const float option_y = screen_height - 45.0f * scale;

  for (const auto &[name, action]: options) {
    if (scene_manager.UI().TextButton(name, {x, option_y}, option_size)) {
      action();
    }

    x += scene_manager.UI().Text().Measure(name, option_size).x;
    x += option_gap;
  }
}

#ifndef INC_2D_GAME_UIMANAGER_H
#define INC_2D_GAME_UIMANAGER_H
#include <algorithm>
#include <cmath>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "../Textures.h"
#include "Alert.h"
#include "Dialog.h"
#include "Menu.h"
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

  void Alert(const std::string &message, const AlertLevel level = AlertLevel::Info, const float duration = 3.0f) const {
    alerts.Show(message, level, duration);
  }

  void DrawAlerts() const { alerts.Draw(text, textures, Scale()); }

  void DrawMenu(const Menu &menu) const { menu.Draw(text, Scale(), TEXT_COLOR, HOVERED_TEXT_COLOR); }

  void ShowDialog(std::string message, std::vector<Dialog::Button> buttons = {}) const {
    dialog.emplace(std::move(message), std::nullopt, std::move(buttons));
  }

  void ShowDialog(std::string title, std::string message, std::vector<Dialog::Button> buttons = {}) const {
    dialog.emplace(std::move(message), std::move(title), std::move(buttons));
  }

  void ShowQuitDialog() const {
    ShowDialog("Quit game?", "Are you sure you want to quit?",
               {{"Cancel", {}}, {"Quit", [] { CloseWindow(); }, Textures::ALERT_WARNING_ICON_RECT}});
  }

  void CloseDialog() const { dialog.reset(); }

  [[nodiscard]] bool HasDialog() const { return dialog.has_value(); }

  void DrawDialog() const {
    if (!dialog.has_value()) {
      return;
    }

    const std::optional<std::size_t> selected_button =
        dialog->Draw(text, textures, Scale(), TEXT_COLOR, HOVERED_TEXT_COLOR);
    if (!selected_button.has_value()) {
      return;
    }

    const Dialog selected_dialog = std::move(*dialog);
    dialog.reset();
    selected_dialog.Trigger(*selected_button);
  }

  [[nodiscard]] TextRenderer &Text() { return text; }
  [[nodiscard]] const TextRenderer &Text() const { return text; }

private:
  TextRenderer text;
  const Textures &textures;
  mutable AlertManager alerts;
  mutable std::optional<Dialog> dialog;
};

#endif

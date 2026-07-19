#ifndef INC_2D_GAME_TEXTURES_H
#define INC_2D_GAME_TEXTURES_H
#include "raylib-cpp.hpp"

enum class TextureId {
  Characters,
  Items,
  World,
};

class Textures {
public:
  void Load();

  static constexpr Rectangle INVENTORY_SLOT_RECT = {195, 0, 64, 64};

  static constexpr Rectangle ALERT_BACKGROUND_RECT{
      128.0f,
      131.0f,
      64.0f,
      76.0f,
  };

  static constexpr Rectangle ALERT_INFO_ICON_RECT{142.0f, 37.0f, 4.0f, 10.0f};
  static constexpr Rectangle ALERT_WARNING_ICON_RECT{142.0f, 54.0f, 4.0f, 10.0f};
  static constexpr Rectangle ALERT_ERROR_ICON_RECT{142.0f, 71.0f, 4.0f, 10.0f};

  Textures() { Load(); }

  [[nodiscard]] const raylib::Texture2D &Characters() const { return characters; }
  [[nodiscard]] const raylib::Texture2D &Tiles() const { return tiles; }
  [[nodiscard]] const raylib::Texture2D &UI() const { return ui; }
  [[nodiscard]] const raylib::Texture2D &UI2() const { return ui2; }

private:
  raylib::Texture2D characters{};
  raylib::Texture2D tiles{};
  raylib::Texture2D ui{};
  raylib::Texture2D ui2{};
};

#endif

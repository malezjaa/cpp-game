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
  void Unload() const;

  static constexpr Rectangle INVENTORY_SLOT_RECT = {195, 0, 64, 64};

  Textures() { Load(); }
  ~Textures() { Unload(); }

  [[nodiscard]] const Texture2D &Characters() const { return characters; }
  [[nodiscard]] const Texture2D &Tiles() const { return tiles; }
  [[nodiscard]] const Texture2D &UI() const { return ui; }

private:
  Texture2D characters{};
  Texture2D tiles{};
  Texture2D ui{};
};

#endif

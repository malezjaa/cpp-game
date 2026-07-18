#ifndef INC_2D_GAME_INVENTORY_H
#define INC_2D_GAME_INVENTORY_H
#include <optional>

#include "Textures.h"
#include "items/Item.h"

class HotbarSlot {
public:
  std::optional<ItemInstance> item;
  std::uint8_t slot;

  explicit HotbarSlot(const std::uint8_t slot) : slot(slot) {}
};

class Hotbar {
public:
  std::vector<HotbarSlot> slots;
  const Textures &textures;

  explicit Hotbar(const Textures &textures);

  void Draw();
};


#endif

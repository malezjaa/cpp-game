#ifndef INC_2D_GAME_ITEMREGISTRY_H
#define INC_2D_GAME_ITEMREGISTRY_H
#include <unordered_map>

#include "Item.h"

class ItemRegistry {
public:
  [[nodiscard]] const ItemDefinition &Get(const ItemId id) const { return definitions.at(id); }

private:
  std::unordered_map<ItemId, ItemDefinition> definitions;
};

#endif

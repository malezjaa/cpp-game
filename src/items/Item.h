#ifndef INC_2D_GAME_ITEM_H
#define INC_2D_GAME_ITEM_H
#include <memory>
#include <string>
#include "raylib-cpp.hpp"

enum class ItemId {};

class ItemBehavior {
public:
  virtual ~ItemBehavior() = default;

  // virtual void onUse(Entity &user) {}
  // virtual void onEquip(Entity &user) {}
  // virtual void onUnequip(Entity &user) {}
  // virtual void onTick(Entity &user, float dt) {}
};

struct ItemDefinition {
  ItemId id;
  std::string name;
  Rectangle sprite;
  int maxStack = 1;
  std::shared_ptr<ItemBehavior> behavior;
};

struct ItemInstance {
  ItemId def;
  int quantity = 1;
  int durability = -1;
};


#endif

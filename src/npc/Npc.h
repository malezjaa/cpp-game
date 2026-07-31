#ifndef INC_2D_GAME_NPC_H
#define INC_2D_GAME_NPC_H
#include <entt/entity/entity.hpp>

#include "NpcDefinition.h"

class Npc {
public:
  explicit Npc(entt::registry &registry, NpcId);

private:
  entt::entity entity;
  entt::registry &registry;
};

#endif

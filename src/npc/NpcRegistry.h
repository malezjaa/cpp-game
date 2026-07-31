#ifndef INC_2D_GAME_NPCREGISTRY_H
#define INC_2D_GAME_NPCREGISTRY_H
#include <entt/entity/registry.hpp>

#include "Npc.h"
#include "NpcDefinition.h"

class NpcRegistry {
public:
  explicit NpcRegistry(entt::registry &);

  [[nodiscard]] const Npc &Get(const NpcId id) const { return npcs.at(id); };

private:
  std::unordered_map<NpcId, Npc> npcs;
};

#endif

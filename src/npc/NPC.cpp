#include "NPC.h"

#include <entt/entity/registry.hpp>

entt::entity NPC::CreateNPC(entt::registry &registry) {
  const auto entity = registry.create();
  return entity;
};

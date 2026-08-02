#include "map_transitions.h"

#include <entt/entity/registry.hpp>

#include "../ecs/components.h"
#include "Map.h"
#include "collisions.h"

void HandleMapTransitions(entt::registry &registry, const Map &map, const entt::entity player) {
  auto &position = registry.get<Position>(player);
  auto &velocity = registry.get<Velocity>(player);
  const auto &collider = registry.get<Collider>(player);

  for (const auto &[transition_points, map_id]: map.transitions) {
    if (CheckCollisions(transition_points, registry, player, GetBounds(position, collider))) {
    }
  }
}



#ifndef INC_2D_GAME_COLLISIONS_H
#define INC_2D_GAME_COLLISIONS_H
#include <Vector2.hpp>
#include <entt/entity/registry.hpp>

#include "../world/Map.h"
#include "Components.h"

struct Collider {
  Vector2 offset{};
  Vector2 size{10.0f, 8.0f};
};

void UpdateMovementAndCollisions(entt::registry &registry, const Map &map, float deltaTime);
Rectangle GetBounds(const Position &position, const Collider &collider);

#endif



#ifndef INC_2D_GAME_COLLISIONS_H
#define INC_2D_GAME_COLLISIONS_H
#include <entt/entity/registry.hpp>

#include "../ecs/components.h"
#include "Map.h"

struct Collider {
  Vector2 offset{};
  Vector2 size{10.0f, 8.0f};
};

void UpdateMovementAndCollisions(entt::registry &registry, const Map &map, float deltaTime, bool handle_collisions);
Rectangle GetBounds(const Position &position, const Collider &collider);
bool CheckCollisionLineRec(Vector2 start, Vector2 end, Rectangle rect);
bool CheckCollisions(const std::vector<MapCollider> &colliders, entt::registry &registry, const entt::entity &entity,
                     Rectangle bounds);

#endif

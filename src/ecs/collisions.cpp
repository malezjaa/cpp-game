#include "collisions.h"

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "Components.h"

struct Map;

Rectangle GetBounds(const Position &position, const Collider &collider) {
  return {
      position.value.x + collider.offset.x,
      position.value.y + collider.offset.y,
      collider.size.x,
      collider.size.y,
  };
}

bool CollidesWithMap(const Rectangle bounds, const Map &map) {
  for (const Rectangle obstacle: map.collisions) {
    if (CheckCollisionRecs(bounds, obstacle)) {
      return true;
    }
  }

  return false;
}

void UpdateMovementAndCollisions(entt::registry &registry, const Map &map, const float deltaTime) {
  for (const auto view = registry.view<Position, Velocity, Collider>(); const entt::entity entity: view) {
    auto &position = registry.get<Position>(entity);
    auto &velocity = registry.get<Velocity>(entity);
    const auto &collider = registry.get<Collider>(entity);

    position.value.x += velocity.value.x * deltaTime;

    if (CollidesWithMap(GetBounds(position, collider), map)) {
      position.value.x -= velocity.value.x * deltaTime;
      velocity.value.x = 0.0f;
    }

    position.value.y += velocity.value.y * deltaTime;

    if (CollidesWithMap(GetBounds(position, collider), map)) {
      position.value.y -= velocity.value.y * deltaTime;
      velocity.value.y = 0.0f;
    }
  }
}

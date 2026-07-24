#include "collisions.h"

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include "Components.h"

Rectangle GetBounds(const Position &position, const Collider &collider) {
  return {
      position.value.x + collider.offset.x,
      position.value.y + collider.offset.y,
      collider.size.x,
      collider.size.y,
  };
}

bool CheckCollisionLineRec(const Vector2 start, const Vector2 end, const Rectangle rect) {
  if (CheckCollisionPointRec(start, rect) || CheckCollisionPointRec(end, rect)) {
    return true;
  }

  const Vector2 topLeft{rect.x, rect.y};
  const Vector2 topRight{rect.x + rect.width, rect.y};
  const Vector2 bottomLeft{rect.x, rect.y + rect.height};
  const Vector2 bottomRight{rect.x + rect.width, rect.y + rect.height};

  Vector2 collisionPoint{};

  return CheckCollisionLines(start, end, topLeft, topRight, &collisionPoint) ||
         CheckCollisionLines(start, end, topRight, bottomRight, &collisionPoint) ||
         CheckCollisionLines(start, end, bottomRight, bottomLeft, &collisionPoint) ||
         CheckCollisionLines(start, end, bottomLeft, topLeft, &collisionPoint);
}

bool CollidesWithMap(const Rectangle bounds, const Map &map) {
  for (const Rectangle obstacle: map.collisions) {
    if (CheckCollisionRecs(bounds, obstacle)) {
      return true;
    }
  }

  for (const auto &points: map.points) {
    if (points.size() < 2) {
      continue;
    }

    for (std::size_t i = 0; i + 1 < points.size(); ++i) {
      if (CheckCollisionLineRec(points[i], points[i + 1], bounds)) {
        return true;
      }
    }

    if (points.size() > 2 && CheckCollisionLineRec(points.back(), points.front(), bounds)) {
      return true;
    }
  }

  return false;
}

void UpdateMovementAndCollisions(entt::registry &registry, const Map &map, const float deltaTime,
                                 const bool handle_collisions) {
  for (const auto view = registry.view<Position, Velocity, Collider>(); const entt::entity entity: view) {

    auto &position = registry.get<Position>(entity);
    auto &velocity = registry.get<Velocity>(entity);
    const auto &collider = registry.get<Collider>(entity);

    position.value.x += velocity.value.x * deltaTime;

    if (CollidesWithMap(GetBounds(position, collider), map) && handle_collisions) {
      position.value.x -= velocity.value.x * deltaTime;
      velocity.value.x = 0.0f;
    }

    position.value.y += velocity.value.y * deltaTime;

    if (CollidesWithMap(GetBounds(position, collider), map) && handle_collisions) {
      position.value.y -= velocity.value.y * deltaTime;
      velocity.value.y = 0.0f;
    }
  }
}

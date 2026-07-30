#include <entt/entity/registry.hpp>

#include "../animations.h"
#include "Components.h"
#include "collisions.h"

void UpdateMovement(entt::registry &registry, const float deltaTime) {
  for (const auto view = registry.view<Position, Velocity>(entt::exclude<Collider>); const entt::entity entity: view) {
    auto &[pos] = registry.get<Position>(entity);
    const auto &[velocity] = registry.get<Velocity>(entity);

    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
  }
}

void UpdateWalkTarget(entt::registry &registry, const float deltaTime) {
  std::vector<entt::entity> arrived;

  const auto view = registry.view<Position, Velocity, MoveTarget>();

  for (const entt::entity entity: view) {
    const auto &[pos] = view.get<Position>(entity);
    auto &[velocity] = view.get<Velocity>(entity);
    const auto &[target, speed, stopDistance] = view.get<MoveTarget>(entity);

    const Vector2 offset{
        target.x - pos.x,
        target.y - pos.y,
    };

    const float distance = Vector2Length(offset);

    if (distance <= stopDistance) {
      velocity = {};
      arrived.push_back(entity);
      continue;
    }

    const float maximumSpeedWithoutOvershooting = distance / deltaTime;
    const float actualSpeed = std::min(speed, maximumSpeedWithoutOvershooting);

    velocity = Vector2Scale(Vector2Normalize(offset), actualSpeed);
  }

  for (const entt::entity entity: arrived) {
    registry.remove<MoveTarget>(entity);
  }
}

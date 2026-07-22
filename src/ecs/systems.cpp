#include <entt/entity/registry.hpp>

#include "Components.h"

void SetAnimationState(AnimatedSprite &sprite, const AnimationState newState) {
  if (sprite.state == newState) {
    return;
  }

  sprite.state = newState;
  sprite.currentFrame = 0;
  sprite.elapsed = 0.0f;
}

void UpdateMovement(entt::registry &registry, const float deltaTime) {
  for (const auto view = registry.view<Position, Velocity>(); const entt::entity entity: view) {
    auto &[pos] = registry.get<Position>(entity);
    const auto &[velocity] = registry.get<Velocity>(entity);

    pos.x += velocity.x * deltaTime;
    pos.y += velocity.y * deltaTime;
  }
}

constexpr float ANIMATION_SPEED = 0.5f;

void UpdateAnimations(entt::registry &registry, const float deltaTime) {
  for (const auto view = registry.view<AnimatedSprite>(); const entt::entity entity: view) {
    auto &sprite = registry.get<AnimatedSprite>(entity);
    const auto &clip = sprite.clips[AnimationIndex(sprite.state)];

    if (clip.frameCount <= 1 || clip.frameDuration <= 0.0f) {
      sprite.currentFrame = 0;
      sprite.elapsed = 0.0f;
      continue;
    }

    sprite.elapsed += deltaTime * ANIMATION_SPEED;

    while (sprite.elapsed >= clip.frameDuration) {
      sprite.elapsed -= clip.frameDuration;
      sprite.currentFrame = (sprite.currentFrame + 1) % clip.frameCount;
    }
  }
}

void DrawAnimatedSprites(entt::registry &registry, const Textures &textures) {
  for (const auto view = registry.view<Position, AnimatedSprite>(); const entt::entity entity: view) {
    const auto &[pos] = registry.get<Position>(entity);
    const auto &sprite = registry.get<AnimatedSprite>(entity);

    const auto &clip = sprite.clips[AnimationIndex(sprite.state)];

    Rectangle source = clip.frames[sprite.currentFrame];

    if (sprite.facing == FacingDirection::Left) {
      source.width = -std::abs(source.width);
    } else {
      source.width = std::abs(source.width);
    }

    const Rectangle destination{
        pos.x,
        pos.y,
        std::abs(source.width) * sprite.scale,
        std::abs(source.height) * sprite.scale,
    };

    DrawTexturePro(textures.Characters(), source, destination, Vector2{}, 0.0f, WHITE);
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

void UpdateMovementAnimations(entt::registry &registry) {
  const auto view = registry.view<Velocity, AnimatedSprite>();

  for (const entt::entity entity: view) {
    const auto &[velocity] = view.get<Velocity>(entity);
    auto &sprite = view.get<AnimatedSprite>(entity);

    const bool moving = velocity.x != 0.0f || velocity.y != 0.0f;

    SetAnimationState(sprite, moving ? AnimationState::Walking : AnimationState::Idle);

    if (velocity.x < 0.0f) {
      sprite.facing = FacingDirection::Left;
    } else if (velocity.x > 0.0f) {
      sprite.facing = FacingDirection::Right;
    }
  }
}

#include "Player.h"

#include "Textures.h"
#include "ecs/Components.h"
#include "ecs/systems.h"

constexpr Rectangle IDLE_RECT = {
    645.0f,
    0.0f,
    128.0f,
    128.0f,
};

constexpr Rectangle WALK_A = {
    0.0f,
    129.0f,
    128.0f,
    128.0f,
};

constexpr Rectangle WALK_B = {
    129.0f,
    129.0f,
    128.0f,
    128.0f,
};

entt::entity Player::CreateEntity(entt::registry &registry, const Vector2 position) {
  const entt::entity player = registry.create();

  registry.emplace<Position>(player, Position{position});
  registry.emplace<Velocity>(player);
  registry.emplace<Health>(player, Health{100, 100});
  registry.emplace<PlayerControlled>(player);

  AnimatedSprite sprite{};

  sprite.clips[AnimationIndex(AnimationState::Idle)] = AnimationClip{
      .frames = {IDLE_RECT},
      .frameCount = 1,
      .frameDuration = 0.2f,
  };

  sprite.clips[AnimationIndex(AnimationState::Walking)] = AnimationClip{
      .frames = {WALK_A, WALK_B},
      .frameCount = 2,
      .frameDuration = 0.15f,
  };

  sprite.clips[AnimationIndex(AnimationState::Running)] = AnimationClip{
      .frames = {WALK_A, WALK_B},
      .frameCount = 2,
      .frameDuration = 0.08f,
  };

  registry.emplace<AnimatedSprite>(player, sprite);

  return player;
}

void UpdatePlayerInput(entt::registry &registry) {
  const auto view = registry.view<Velocity, AnimatedSprite, PlayerControlled>();

  for (const entt::entity entity: view) {
    auto &[value] = registry.get<Velocity>(entity);
    auto &sprite = registry.get<AnimatedSprite>(entity);

    Vector2 direction{
        static_cast<float>(IsKeyDown(KEY_D)) - static_cast<float>(IsKeyDown(KEY_A)),
        static_cast<float>(IsKeyDown(KEY_S)) - static_cast<float>(IsKeyDown(KEY_W)),
    };

    const bool isMoving = direction.x != 0.0f || direction.y != 0.0f;

    const bool isRunning = isMoving && IsKeyDown(KEY_LEFT_SHIFT);

    if (!isMoving) {
      value = {};
      SetAnimationState(sprite, AnimationState::Idle);
      continue;
    }

    const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    direction.x /= length;
    direction.y /= length;

    constexpr float WALK_SPEED = 200.0f;
    constexpr float RUN_MULTIPLIER = 1.5f;

    const float speed = WALK_SPEED * (isRunning ? RUN_MULTIPLIER : 1.0f);

    value = {
        direction.x * speed,
        direction.y * speed,
    };

    if (direction.x < 0.0f) {
      sprite.facing = FacingDirection::Left;
    } else if (direction.x > 0.0f) {
      sprite.facing = FacingDirection::Right;
    }

    SetAnimationState(sprite, isRunning ? AnimationState::Running : AnimationState::Walking);
  }
}

#include "Player.h"

#include "Textures.h"
#include "ecs/Components.h"
#include "ecs/collisions.h"
#include "ecs/systems.h"
#include "world/Map.h"

namespace {

  AnimationClip MakeClip(const float frameWidth, const float frameHeight, const std::size_t frameCount,
                         const float frameDuration) {
    AnimationClip clip{
        .frameCount = frameCount,
        .frameDuration = frameDuration,
    };

    for (std::size_t frame = 0; frame < frameCount; ++frame) {
      clip.frames[frame] = {
          frameWidth * static_cast<float>(frame),
          0.0f,
          frameWidth,
          frameHeight,
      };
    }

    return clip;
  }

  float FrameWidth(const FacingDirection direction) {
    return direction == FacingDirection::Left || direction == FacingDirection::Right ? 10.0f : 11.0f;
  }

  float PickupFrameWidth(const FacingDirection direction) {
    return direction == FacingDirection::Left || direction == FacingDirection::Right ? 10.0f : 11.0f;
  }

  float PickupFrameHeight(const FacingDirection direction) { return direction == FacingDirection::Up ? 15.0f : 16.0f; }

  float PunchFrameWidth(const FacingDirection direction) {
    return direction == FacingDirection::Left || direction == FacingDirection::Right ? 13.0f : 11.0f;
  }

  float PunchFrameHeight(const FacingDirection direction) {
    return direction == FacingDirection::Left || direction == FacingDirection::Right ? 16.0f : 17.0f;
  }

} // namespace

entt::entity Player::CreateEntity(entt::registry &registry, const Vector2 position) {
  const entt::entity player = registry.create();

  registry.emplace<Position>(player, Position{position});
  registry.emplace<Velocity>(player);
  registry.emplace<Collider>(player, Collider{
                                         .size = {12.0f, 16.0f},
                                     });
  registry.emplace<Health>(player, Health{100, 100});
  registry.emplace<PlayerControlled>(player);

  AnimatedSprite sprite{};

  for (std::size_t i = 0; i < FACING_DIRECTION_COUNT; ++i) {
    const auto direction = static_cast<FacingDirection>(i);
    const float frameWidth = FrameWidth(direction);

    sprite.clips[AnimationIndex(AnimationState::Idle)][i] = MakeClip(frameWidth, 16.0f, 6, 0.2f);
    sprite.clips[AnimationIndex(AnimationState::Walking)][i] = MakeClip(frameWidth, 17.0f, 6, 0.15f);
    sprite.clips[AnimationIndex(AnimationState::Running)][i] = MakeClip(frameWidth, 17.0f, 6, 0.08f);
    sprite.clips[AnimationIndex(AnimationState::Pickup)][i] =
        MakeClip(PickupFrameWidth(direction), PickupFrameHeight(direction), 3, 0.12f);
    sprite.clips[AnimationIndex(AnimationState::Punch)][i] =
        MakeClip(PunchFrameWidth(direction), PunchFrameHeight(direction), 4, 0.1f);
    sprite.clips[AnimationIndex(AnimationState::Death)][i] = MakeClip(21.0f, 16.0f, 6, 0.12f);
  }

  registry.emplace<AnimatedSprite>(player, sprite);

  return player;
}

void UpdatePlayerInput(entt::registry &registry, const Map &map) {
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

    constexpr float WALK_SPEED = 150.0f;
    constexpr float RUN_MULTIPLIER = 1.3f;

    const float speed = WALK_SPEED * (isRunning ? RUN_MULTIPLIER : 1.0f);

    value = {
        direction.x * speed,
        direction.y * speed,
    };

    if (std::abs(direction.x) > std::abs(direction.y)) {
      sprite.facing = direction.x < 0.0f ? FacingDirection::Left : FacingDirection::Right;
    } else {
      sprite.facing = direction.y < 0.0f ? FacingDirection::Up : FacingDirection::Down;
    }

    SetAnimationState(sprite, isRunning ? AnimationState::Running : AnimationState::Walking);
  }
}

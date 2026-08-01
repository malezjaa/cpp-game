#ifndef INC_2D_GAME_ANIMATIONS_H
#define INC_2D_GAME_ANIMATIONS_H
#include <array>
#include <cstddef>
#include <cstdint>
#include <entt/entity/registry.hpp>
#include <raylib.h>

#include "Textures.h"

enum class AnimationState : std::uint8_t {
  Idle,
  Walking,
  Running,
  Pickup,
  Punch,
  Death,
  Count,
};

enum class FacingDirection : std::uint8_t {
  Down,
  Left,
  Right,
  Up,
  Count,
};

constexpr std::size_t ANIMATION_STATE_COUNT = static_cast<std::size_t>(AnimationState::Count);
constexpr std::size_t FACING_DIRECTION_COUNT = static_cast<std::size_t>(FacingDirection::Count);

constexpr std::size_t AnimationIndex(const AnimationState state) { return static_cast<std::size_t>(state); }
constexpr std::size_t FacingDirectionIndex(const FacingDirection direction) {
  return static_cast<std::size_t>(direction);
}

struct AnimationClip {
  std::array<Rectangle, 6> frames{};

  std::size_t frameCount = 1;
  float frameDuration = 0.15f;
};

struct AnimatedSprite {
  std::array<std::array<AnimationClip, FACING_DIRECTION_COUNT>, ANIMATION_STATE_COUNT> clips{};

  AnimationState state = AnimationState::Idle;
  FacingDirection facing = FacingDirection::Down;

  std::size_t currentFrame = 0;
  float elapsed = 0.0f;
  float scale = 1.0f;
};

AnimationClip MakeClip(float frameWidth, float frameHeight, std::size_t frameCount, float frameDuration);

void SetAnimationState(AnimatedSprite &sprite, AnimationState newState);
void UpdateAnimations(entt::registry &registry, float deltaTime);
void DrawAnimatedSprites(entt::registry &registry, const Textures &textures);
void UpdateMovementAnimations(entt::registry &registry);

inline Vector2 GetSpriteSize(const AnimatedSprite &sprite) {
  const auto stateIndex = std::to_underlying(sprite.state);
  const auto facingIndex = std::to_underlying(sprite.facing);

  const AnimationClip &clip = sprite.clips[stateIndex][facingIndex];
  const Rectangle &frame = clip.frames[sprite.currentFrame];

  return {
      std::abs(frame.width) * sprite.scale,
      std::abs(frame.height) * sprite.scale,
  };
}
#endif

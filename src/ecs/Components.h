#ifndef INC_2D_GAME_COMPONENTS_H
#define INC_2D_GAME_COMPONENTS_H
#include <raylib.h>

#include "../Textures.h"

struct Position {
  Vector2 value{};
};

struct Velocity {
  Vector2 value{};
};

struct Sprite {
  TextureId id;
  Rectangle source{};
  float scale = 1.0f;
};

struct Health {
  int current = 100;
  int maximum = 100;
};

struct MoveTarget {
  Vector2 target;
  float speed;
  float stopDistance = 2.0f;
};

struct PlayerControlled {};

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
#endif

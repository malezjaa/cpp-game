#include "animations.h"
#include <cstddef>

#include "ecs/Components.h"

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

void SetAnimationState(AnimatedSprite &sprite, const AnimationState newState) {
  if (sprite.state == newState) {
    return;
  }

  sprite.state = newState;
  sprite.currentFrame = 0;
  sprite.elapsed = 0.0f;
}

constexpr float ANIMATION_SPEED = 0.5f;

void UpdateAnimations(entt::registry &registry, const float deltaTime) {
  for (const auto view = registry.view<AnimatedSprite>(); const entt::entity entity: view) {
    auto &sprite = registry.get<AnimatedSprite>(entity);
    const auto &clip = sprite.clips[AnimationIndex(sprite.state)][FacingDirectionIndex(sprite.facing)];

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

    const auto &clip = sprite.clips[AnimationIndex(sprite.state)][FacingDirectionIndex(sprite.facing)];

    Rectangle source = clip.frames[sprite.currentFrame];

    const Rectangle destination{
        std::round(pos.x),
        std::round(pos.y),
        std::abs(source.width) * sprite.scale,
        std::abs(source.height) * sprite.scale,
    };

    const std::size_t textureIndex =
        AnimationIndex(sprite.state) * FACING_DIRECTION_COUNT + FacingDirectionIndex(sprite.facing);
    DrawTexturePro(textures.CharacterAnimation(textureIndex), source, destination, Vector2{}, 0.0f, WHITE);
  }
}

void UpdateMovementAnimations(entt::registry &registry) {
  const auto view = registry.view<Velocity, AnimatedSprite>(entt::exclude<PlayerControlled>);

  for (const entt::entity entity: view) {
    const auto &[velocity] = view.get<Velocity>(entity);
    auto &sprite = view.get<AnimatedSprite>(entity);

    const bool moving = velocity.x != 0.0f || velocity.y != 0.0f;

    SetAnimationState(sprite, moving ? AnimationState::Walking : AnimationState::Idle);

    if (std::abs(velocity.x) > std::abs(velocity.y)) {
      sprite.facing = velocity.x < 0.0f ? FacingDirection::Left : FacingDirection::Right;
    } else if (velocity.y != 0.0f) {
      sprite.facing = velocity.y < 0.0f ? FacingDirection::Up : FacingDirection::Down;
    }
  }
}

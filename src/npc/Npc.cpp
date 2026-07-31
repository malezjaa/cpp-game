#include "Npc.h"

#include <entt/entity/registry.hpp>

#include "../animations.h"
#include "../ecs/components.h"
#include "../world/collisions.h"

Npc::Npc(entt::registry &registry, const NpcId id) : registry(registry) {
  entity = registry.create();

  registry.emplace<Position>(entity, Position{Vector2{1084.0f, 600.0f}});
  registry.emplace<Velocity>(entity);
  registry.emplace<Collider>(entity, Collider{
                                         .offset = {1.0f, 11.0f},
                                         .size = {8.0f, 5.0f},
                                     });
  registry.emplace<Health>(entity, Health{100, 100});
  registry.emplace<NpcEntity>(entity, NpcEntity{id});

  AnimatedSprite sprite{};

  for (std::size_t i = 0; i < FACING_DIRECTION_COUNT; ++i) {
    const auto direction = static_cast<FacingDirection>(i);
    const float frameWidth = direction == FacingDirection::Left || direction == FacingDirection::Right ? 10.0f : 11.0f;

    sprite.clips[AnimationIndex(AnimationState::Idle)][i] = MakeClip(frameWidth, 16.0f, 6, 0.2f);
    sprite.clips[AnimationIndex(AnimationState::Walking)][i] = MakeClip(frameWidth, 17.0f, 6, 0.15f);
    sprite.clips[AnimationIndex(AnimationState::Running)][i] = MakeClip(frameWidth, 17.0f, 6, 0.08f);
    sprite.clips[AnimationIndex(AnimationState::Death)][i] = MakeClip(21.0f, 16.0f, 6, 0.12f);
  }

  registry.emplace<AnimatedSprite>(entity, sprite);
};

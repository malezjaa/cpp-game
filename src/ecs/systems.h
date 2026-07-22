#ifndef INC_2D_GAME_SYSTEMS_H
#define INC_2D_GAME_SYSTEMS_H
#include "Components.h"

void SetAnimationState(AnimatedSprite &sprite, AnimationState newState);
void UpdatePlayerInput(entt::registry &registry);
void UpdateMovement(entt::registry &registry, float deltaTime);
void UpdateAnimations(entt::registry &registry, float deltaTime);
void DrawAnimatedSprites(entt::registry &registry, const Textures &textures);
void UpdateWalkTarget(entt::registry &registry, float deltaTime);
void UpdateMovementAnimations(entt::registry &registry);

#endif

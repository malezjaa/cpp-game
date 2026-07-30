#ifndef INC_2D_GAME_SYSTEMS_H
#define INC_2D_GAME_SYSTEMS_H
#include "../world/Map.h"

void UpdatePlayerInput(entt::registry &registry, const Map &);
void UpdateMovement(entt::registry &registry, float deltaTime);
void UpdateWalkTarget(entt::registry &registry, float deltaTime);

#endif

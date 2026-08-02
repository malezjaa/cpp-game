#ifndef INC_2D_GAME_MAP_TRANSITIONS_H
#define INC_2D_GAME_MAP_TRANSITIONS_H
#include <entt/entity/entity.hpp>

#include "Map.h"
void HandleMapTransitions(entt::registry &registry, const Map &map, entt::entity player);

#endif

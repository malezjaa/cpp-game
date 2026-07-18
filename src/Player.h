#ifndef INC_2D_GAME_PLAYER_H
#define INC_2D_GAME_PLAYER_H
#include "raylib-cpp.hpp"

#include <entt/entity/registry.hpp>

class Player {
public:
  static entt::entity CreateEntity(entt::registry &registry, Vector2 position);
};

#endif

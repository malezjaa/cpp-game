#ifndef INC_2D_GAME_GAME_H
#define INC_2D_GAME_GAME_H
#include <raylib-cpp.hpp>
#include "Player.h"
#include "Textures.h"

class Game {
  Textures textures;
  entt::registry registry;

  entt::entity player = entt::null;
  Camera2D camera{};

public:
  explicit Game(const Camera2D &);
  void Update();
  void Draw();
  void DrawUI();
};


#endif

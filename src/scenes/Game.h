#ifndef INC_2D_GAME_GAME_H
#define INC_2D_GAME_GAME_H
#include <raylib-cpp.hpp>

#include "../Player.h"
#include "../Textures.h"
#include "SceneManager.h"

class Game : public Scene {
public:
  explicit Game(Camera2D &, SceneManager &);

  void Update() override;
  void Draw() override;
  void DrawUI();

private:
  entt::registry registry;
  entt::entity player = entt::null;
  Camera2D &camera;
  SceneManager &scene_manager;
};


#endif

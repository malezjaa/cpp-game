#ifndef INC_2D_GAME_GAME_H
#define INC_2D_GAME_GAME_H
#include <raylib-cpp.hpp>

#include "../Player.h"
#include "../ui/Menu.h"
#include "SceneManager.h"

enum class GameState { Playing, Paused };

class Game : public Scene {
public:
  explicit Game(Camera2D &, SceneManager &);

  void Update() override;
  void Draw() override;

  void UpdateGame();
  void DrawUI();
  void DrawGameUI();
  void DrawPauseMenuUI();

private:
  entt::registry registry;
  entt::entity player = entt::null;
  Camera2D &camera;
  SceneManager &scene_manager;
  GameState state = GameState::Playing;
  Menu menu;
};


#endif

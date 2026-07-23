#include "Game.h"

#include <magic_enum/magic_enum.hpp>
#include <map>

#include "../Player.h"
#include "../ecs/Components.h"
#include "../ecs/collisions.h"
#include "../ecs/systems.h"
#include "imgui.h"

Game::Game(Camera2D &camera, SceneManager &scene_manager) :
    camera(camera), scene_manager(scene_manager), menu(std::vector<Menu::Option>{
                                                      {
                                                          "Continue",
                                                          [this] { this->state = GameState::Playing; },
                                                      },
                                                      {
                                                          "Quit",
                                                          [this] { this->scene_manager.UI().ShowQuitDialog(); },
                                                      },
                                                  }),
    world{} {

  player = Player::CreateEntity(registry, Vector2{1024.0f, 500.0f});
}

void Game::Update() {
  if (IsKeyPressed(KEY_ESCAPE)) {
    state = state == GameState::Paused ? GameState::Playing : GameState::Paused;
  }

  switch (state) {
    case GameState::Playing:
      UpdateGame();
      break;

    case GameState::Paused:
      break;
  }
}

void Game::UpdateGame() {
  const float deltaTime = std::min(GetFrameTime(), 1.0f / 30.0f);

  UpdateWalkTarget(registry, deltaTime);
  UpdatePlayerInput(registry, world.GetMap());
  UpdateMovement(registry, deltaTime);
  UpdateMovementAndCollisions(registry, world.GetMap(), deltaTime);
  UpdateMovementAnimations(registry);
  UpdateAnimations(registry, deltaTime);

  const auto &[pos] = registry.get<Position>(player);

  constexpr float PLAYER_FRAME_SIZE = 16.0f;
  constexpr float HALF_PLAYER_FRAME_SIZE = PLAYER_FRAME_SIZE / 2.0f;

  camera.target = {
      std::round(pos.x) + HALF_PLAYER_FRAME_SIZE,
      std::round(pos.y) + HALF_PLAYER_FRAME_SIZE,
  };
  camera.offset = {static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f};
}

void Game::Draw() {
  ClearBackground(BLACK);

  BeginMode2D(camera);
  {
    world.Draw(&camera);
    DrawAnimatedSprites(registry, scene_manager.textures);

    if (scene_manager.dev_tools.colliders) {
      for (const Rectangle &rect: world.GetMap().collisions) {
        DrawRectangleLinesEx(rect, .5f, ORANGE);
      }

      for (const auto &collider: registry.view<Collider, Position>()) {
        const auto &pos = registry.get<Position>(collider);
        const auto &col = registry.get<Collider>(collider);

        Rectangle bounds = GetBounds(pos, col);

        bounds.x = std::round(bounds.x);
        bounds.y = std::round(bounds.y);
        bounds.width = std::round(bounds.width);
        bounds.height = std::round(bounds.height);

        DrawRectangleLinesEx(bounds, 1.0f, ORANGE);
      }
    }
  }

  EndMode2D();

  if (scene_manager.dev_tools.enabled) {
    const auto &[pos] = registry.get<Position>(player);
    ImGui::Begin("Player");
    ImGui::Text("Coordinates: (%.2f, %.2f)", pos.x, pos.y);
    ImGui::End();
  }

  DrawUI();
}

void Game::DrawGameUI() {}

void Game::DrawPauseMenuUI() {
  DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), {0, 0, 0, 0}, {0, 0, 0, 180});
  scene_manager.UI().DrawMenu(menu);
}

void Game::DrawUI() {
  switch (state) {
    case GameState::Playing:
      DrawGameUI();
      break;

    case GameState::Paused:
      DrawPauseMenuUI();
      break;
  }
}

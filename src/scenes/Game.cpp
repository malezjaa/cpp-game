#include "Game.h"

#include <magic_enum/magic_enum.hpp>

#include "../Player.h"
#include "../ecs/Components.h"
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
                                                  }) {
  world.InitializeMaps();

  player = Player::CreateEntity(registry, Vector2{100.0f, 100.0f});
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
  const float deltaTime = GetFrameTime();

  UpdateWalkTarget(registry, deltaTime);
  UpdatePlayerInput(registry);
  UpdateMovement(registry, deltaTime);
  UpdateMovementAnimations(registry);
  UpdateAnimations(registry, deltaTime);

  const auto &[pos] = registry.get<Position>(player);

  constexpr float SPRITE_SIZE = 128.0f;
  constexpr float HALF_SPRITE_SIZE = SPRITE_SIZE / 2.0f;

  camera.target = {
      pos.x + HALF_SPRITE_SIZE,
      pos.y + HALF_SPRITE_SIZE,
  };
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}

void Game::Draw() {
  ClearBackground(RAYWHITE);
  BeginMode2D(camera);
  DrawAnimatedSprites(registry, scene_manager.textures);
  EndMode2D();

  if (scene_manager.dev_tools()) {
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

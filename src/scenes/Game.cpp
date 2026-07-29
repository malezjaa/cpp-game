#include "Game.h"

#include <iostream>
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

  player = Player::CreateEntity(registry, Vector2{1024.0f, 600.0f});
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
  UpdateMovementAndCollisions(registry, world.GetMap(), deltaTime, scene_manager.dev_tools.colliders);
  UpdateMovementAnimations(registry);
  UpdateAnimations(registry, deltaTime);

  AnimateTMX(world.GetMap().tmx_map);

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
    DrawDevHelpers();
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

void Game::DrawDevHelpers() {
  if (scene_manager.dev_tools.draw_colliders) {
    for (const Rectangle &rect: world.GetMap().collisions) {
      DrawRectangleLinesEx(rect, .5f, ORANGE);
    }

    for (const auto &points: world.GetMap().points) {
      if (points.size() < 2) {
        continue;
      }

      DrawLineStrip(points.data(), static_cast<int>(points.size()), ORANGE);
      DrawLineV(points.back(), points.front(), ORANGE);
    }

    for (const auto &collider: registry.view<Collider, Position>()) {
      const auto &pos = registry.get<Position>(collider);
      const auto &col = registry.get<Collider>(collider);

      Rectangle bounds = GetBounds(pos, col);

      bounds.x = std::round(bounds.x);
      bounds.y = std::round(bounds.y);
      bounds.width = std::round(bounds.width);
      bounds.height = std::round(bounds.height);

      DrawRectangleLinesEx(bounds, .5f, ORANGE);
    }
  }

  if (scene_manager.dev_tools.draw_grid_map) {
    for (int x = 0; x <= world.GetMap().width; x += 16) {
      DrawLine(x, 0, x, static_cast<int>(world.GetMap().height), BLUE);
    }

    for (int y = 0; y <= world.GetMap().height; y += 16) {
      DrawLine(0, y, static_cast<int>(world.GetMap().width), y, BLUE);
    }
  }
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

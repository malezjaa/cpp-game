#include "Game.h"

#include <iostream>
#include <magic_enum/magic_enum.hpp>

#include "../Player.h"
#include "../animations.h"
#include "../ecs/components.h"
#include "../ecs/systems.h"
#include "../hud/HealthBar.h"
#include "../npc/nametags.h"
#include "../world/collisions.h"
#include "../world/map_transitions.h"
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
    world{registry} {

  player = Player::CreateEntity(registry, Vector2{1024.0f, 600.0f});
  world.LoadMap(MapId::World, scene_manager.dev_tools.Settings());
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
  UpdateMovementAndCollisions(registry, world.GetMap(), deltaTime, scene_manager.dev_tools.Settings().colliders);
  UpdateMovementAnimations(registry);
  UpdateAnimations(registry, deltaTime);
  HandleMapTransitions(registry, world.GetMap(), player);

  AnimateTMX(world.GetMap().tmx_map);

  const auto &[pos] = registry.get<Position>(player);

  constexpr float PLAYER_FRAME_SIZE = 16.0f;
  constexpr float HALF_PLAYER_FRAME_SIZE = PLAYER_FRAME_SIZE / 2.0f;

  camera.target = {
      std::round(pos.x) + HALF_PLAYER_FRAME_SIZE,
      std::round(pos.y) + HALF_PLAYER_FRAME_SIZE,
  };
  camera.offset = {static_cast<float>(GetScreenWidth()) / 2.0f, static_cast<float>(GetScreenHeight()) / 2.0f};

  scene_manager.dev_tools.Settings().entity_colliders = static_cast<int>(registry.view<Collider>().size());
}

void Game::Draw() {
  ClearBackground(BLACK);
  BeginMode2D(camera);

  {
    world.Draw(&camera);
    DrawAnimatedSprites(registry, scene_manager.textures);
    DrawNameTags(registry, scene_manager.UI().Text());
    DrawDevHelpers();
  }

  EndMode2D();

  auto &dev_tools = scene_manager.dev_tools.Settings();
  if (dev_tools.enabled) {
    const auto &[pos] = registry.get<Position>(player);
    ImGui::Begin("Player");
    ImGui::Text("Coordinates: (%.2f, %.2f)", pos.x, pos.y);
    ImGui::End();

    ImGui::Begin("Collisions");
    ImGui::Text("AABB colliders: %d", dev_tools.aabb_colliders);
    ImGui::Text("Entity colliders: %d", dev_tools.entity_colliders);
    ImGui::Text("Point colliders: %d", dev_tools.point_colliders);

    ImGui::Separator();

    ImGui::Checkbox("Collisions", &dev_tools.colliders);
    ImGui::Checkbox("Draw colliders", &dev_tools.draw_colliders);
    ImGui::Checkbox("Draw grid map", &dev_tools.draw_grid_map);
    ImGui::End();

    ImGui::Begin("Map transitions");
    ImGui::Checkbox("Draw map transitions", &dev_tools.draw_map_transitions);
    ImGui::End();
  }

  DrawUI();
}

void Game::DrawDevHelpers() {
  scene_manager.dev_tools.DrawColliderBounds(world, registry);
  scene_manager.dev_tools.DrawGridMap(world);
  scene_manager.dev_tools.DrawMapTransitions(world);
}

void Game::DrawGameUI() {
  const Health &health = registry.get<Health>(player);
  DrawHealthBar(scene_manager.UI().Text(), scene_manager.textures, health);
}

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

#include "Game.h"

#include "../Player.h"
#include "../ecs/Components.h"
#include "../ecs/systems.h"

Game::Game(Camera2D &camera, SceneManager &scene_manager) : camera(camera), scene_manager(scene_manager) {
  player = Player::CreateEntity(registry, Vector2{100.0f, 100.0f});
}

void Game::Update() {
  const float deltaTime = GetFrameTime();

  UpdatePlayerInput(registry);
  UpdateMovement(registry, deltaTime);
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
}

void Game::DrawUI() {}

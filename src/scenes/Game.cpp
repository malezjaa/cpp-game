#include "Game.h"

#include "../Player.h"
#include "../ecs/Components.h"
#include "../ecs/systems.h"

Game::Game(Camera2D &camera, SceneManager &scene_manager) : camera(camera), scene_manager(scene_manager) {
  textures.Load();
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
}

void Game::Draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  BeginMode2D(camera);
  DrawAnimatedSprites(registry, textures);
  EndMode2D();

  // hotbar.Draw();

  EndDrawing();
}

void Game::DrawUI() {}

#include "Textures.h"

void Textures::Load() {
  characters = LoadTexture("../assets/spritesheets/characters.png");
  tiles = LoadTexture("../assets/spritesheets/tiles.png");
  ui = LoadTexture("../assets/spritesheets/ui.png");
}

void Textures::Unload() const {
  UnloadTexture(characters);
  UnloadTexture(tiles);
}

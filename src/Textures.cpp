#include "Textures.h"

void Textures::Load() {
  static constexpr std::array<const char *, 24> CHARACTER_ANIMATION_PATHS{
      "../assets/character/player/idle/down.png",
      "../assets/character/player/idle/left.png",
      "../assets/character/player/idle/right.png",
      "../assets/character/player/idle/up.png",
      "../assets/character/player/run/down.png",
      "../assets/character/player/run/left.png",
      "../assets/character/player/run/right.png",
      "../assets/character/player/run/up.png",
      "../assets/character/player/run/down.png",
      "../assets/character/player/run/left.png",
      "../assets/character/player/run/right.png",
      "../assets/character/player/run/up.png",
      "../assets/character/player/pickup/down.png",
      "../assets/character/player/pickup/left.png",
      "../assets/character/player/pickup/right.png",
      "../assets/character/player/pickup/up.png",
      "../assets/character/player/punch/down.png",
      "../assets/character/player/punch/left.png",
      "../assets/character/player/punch/right.png",
      "../assets/character/player/punch/up.png",
      "../assets/character/player/death/right.png",
      "../assets/character/player/death/left.png",
      "../assets/character/player/death/right.png",
      "../assets/character/player/death/right.png",
  };

  for (std::size_t i = 0; i < CHARACTER_ANIMATION_PATHS.size(); ++i) {
    characterAnimations[i].Load(CHARACTER_ANIMATION_PATHS[i]);
  }
  tiles.Load("../assets/spritesheets/tiles.png");
  ui.Load("../assets/spritesheets/ui.png");
  ui2.Load("../assets/spritesheets/ui2.png");
}

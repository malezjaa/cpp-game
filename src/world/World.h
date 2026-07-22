
#ifndef INC_2D_GAME_WORLD_H
#define INC_2D_GAME_WORLD_H
#include <unordered_map>
#include "Map.h"

class World {
public:
  void LoadMap();
  void Update(float dt);
  void Draw();
  void InitializeMap();

private:
  Map map;
};
#endif

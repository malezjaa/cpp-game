
#ifndef INC_2D_GAME_WORLD_H
#define INC_2D_GAME_WORLD_H
#include <unordered_map>
#include "Map.h"

class World {
public:
  void LoadMap();
  void Update(float dt);
  void Draw(const Camera2D *camera) const;
  World();

  ~World() { UnloadTMX(map.tmx_map); }

private:
  Map map;
};
#endif

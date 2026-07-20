
#ifndef INC_2D_GAME_WORLD_H
#define INC_2D_GAME_WORLD_H
#include <unordered_map>
#include "Map.h"

class World {
public:
  void LoadMap(MapId id);
  void Update(float dt);
  void Draw();
  void InitializeMaps();

private:
  MapId current_map;
  std::unordered_map<MapId, Map> maps;
};
#endif


#ifndef INC_2D_GAME_WORLD_H
#define INC_2D_GAME_WORLD_H
#include <string_view>
#include <unordered_map>
#include "Map.h"

class World {
public:
  void LoadMap();
  void Update(float dt);
  void Draw(const Camera2D *camera) const;

  Map &GetMap() { return map; }
  [[nodiscard]] const Map &GetMap() const { return map; }

  World();
  ~World() { UnloadTMX(map.tmx_map); }

  const TmxObjectGroup *FindObjectGroup(std::string_view name) const;
  void LoadCollisions();
  void LoadMapTransitions();

private:
  Map map;
};
#endif

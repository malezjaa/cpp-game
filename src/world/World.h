
#ifndef INC_2D_GAME_WORLD_H
#define INC_2D_GAME_WORLD_H
#include <string_view>
#include <unordered_map>
#include "../npc/NpcRegistry.h"
#include "../scenes/SceneManager.h"
#include "Map.h"

class World {
public:
  void LoadMap(MapId, DevToolsSettings &);
  void Draw(const Camera2D *camera) const;

  NpcRegistry &Npcs() { return npcs; }
  [[nodiscard]] const NpcRegistry &Npcs() const { return npcs; }

  Map &GetMap() { return map; }
  [[nodiscard]] const Map &GetMap() const { return map; }

  ~World() { UnloadTMX(map.tmx_map); }

  [[nodiscard]] const TmxObjectGroup *FindObjectGroup(std::string_view name) const;
  void LoadCollisions();
  void LoadMapTransitions();

  explicit World(entt::registry &registry) : map({}), npcs(registry) {}

private:
  Map map;
  NpcRegistry npcs;
};
#endif

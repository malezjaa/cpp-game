#ifndef INC_2D_GAME_DEVTOOLS_H
#define INC_2D_GAME_DEVTOOLS_H
#include <entt/entity/registry.hpp>


class World;
struct DevToolsSettings {
  bool enabled = false;
  bool draw_colliders = false;
  bool colliders = true;
  bool draw_grid_map = false;
  bool draw_map_transitions = false;
  int aabb_colliders = 0;
  int entity_colliders = 0;
  int point_colliders = 0;
};

class DevTools {
public:
  DevToolsSettings &Settings() { return settings; }
  void DrawColliderBounds(const World &world, const entt::registry &registry) const;
  void DrawGridMap(const World &world) const;
  void DrawMapTransitions(const World &world) const;

private:
  DevToolsSettings settings;
};

#endif

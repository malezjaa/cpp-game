#include "World.h"
#include "../third_party/raytmx.h"

World::World() {
  this->map = Map{.tmx_map = LoadTMX("../assets/maps/map.tmx"), .grid = BuildGrid{}};
  if (this->map.tmx_map == nullptr) {
    TraceLog(LOG_ERROR, "Could not load map");
  }
}

void World::Draw(const Camera2D *camera) const { DrawTMX(map.tmx_map, camera, nullptr, 0, 0, WHITE); }

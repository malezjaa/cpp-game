#include "World.h"

#include <iostream>

#include "../third_party/raytmx.h"

World::World() {
  this->map = Map{.tmx_map = LoadTMX("../assets/maps/map.tmx"), .grid = BuildGrid{}};
  if (this->map.tmx_map == nullptr) {
    TraceLog(LOG_ERROR, "Could not load map");
  }

  const TmxLayer *layers = map.tmx_map->layers;
  for (std::size_t i = 0; i < map.tmx_map->layersLength; ++i) {
    if (const auto &layer = layers[i]; layer.type == LAYER_TYPE_OBJECT_GROUP) {
      const TmxObjectGroup &group = layer.exact.objectGroup;

      for (std::size_t j = 0; j < group.objectsLength; ++j) {
        auto &obj = group.objects[j];
        this->map.collisions.emplace_back(obj.aabb.x, obj.aabb.y, obj.aabb.width, obj.aabb.height);
      }
    }
  }
}

void World::Draw(const Camera2D *camera) const { DrawTMX(map.tmx_map, camera, nullptr, 0, 0, WHITE); }

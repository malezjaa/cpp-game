#include "World.h"

#include <algorithm>
#include <iostream>

#include "../third_party/raytmx.h"

#include <array>
#include <cmath>
#include <span>

std::vector<Vector2> GetRotatedRectanglePoints(const TmxObject &obj) {
  const float radians = static_cast<float>(obj.rotation) * DEG2RAD;
  const float cosine = std::cos(radians);
  const float sine = std::sin(radians);

  const Vector2 origin{static_cast<float>(obj.x), static_cast<float>(obj.y)};

  const auto width = static_cast<float>(obj.width);
  const auto height = static_cast<float>(obj.height);
  const std::array<Vector2, 4> localPoints =
      obj.type == OBJECT_TYPE_TILE
          ? std::array<Vector2, 4>{{{0.0f, -height}, {width, -height}, {width, 0.0f}, {0.0f, 0.0f}}}
          : std::array<Vector2, 4>{{{0.0f, 0.0f}, {width, 0.0f}, {width, height}, {0.0f, height}}};

  std::vector<Vector2> points;
  points.reserve(localPoints.size());

  for (const auto [x, y]: localPoints) {
    points.push_back({origin.x + x * cosine - y * sine, origin.y + x * sine + y * cosine});
  }

  return points;
}

bool ColliderEnabled(std::span<const TmxProperty> properties) {
  return std::ranges::any_of(properties, [](const TmxProperty &property) {
    return property.name != nullptr && std::string_view{property.name} == "collide" &&
           property.type == PROPERTY_TYPE_BOOL && property.boolValue;
  });
}

World::World() {
  map = Map{.tmx_map = LoadTMX("../assets/maps/map.tmx"), .grid = BuildGrid{}};
  if (map.tmx_map == nullptr) {
    TraceLog(LOG_ERROR, "Could not load map");
  }

  // Width and height from tmx map are actually number of tiles not pixels
  map.width = map.tmx_map->width * 16;
  map.height = map.tmx_map->height * 16;

  const TmxLayer *layers = map.tmx_map->layers;
  for (std::size_t i = 0; i < map.tmx_map->layersLength; ++i) {
    if (const auto &layer = layers[i]; layer.type == LAYER_TYPE_OBJECT_GROUP) {
      const TmxObjectGroup &group = layer.exact.objectGroup;

      for (std::size_t j = 0; j < group.objectsLength; ++j) {
        auto &obj = group.objects[j];

        if (obj.pointsLength > 0) {
          std::vector<Vector2> points;
          points.reserve(obj.pointsLength);

          for (std::size_t point_i = 0; point_i < obj.pointsLength; ++point_i) {
            points.emplace_back(obj.x + obj.points[point_i].x, obj.y + obj.points[point_i].y);
          }

          map.points.emplace_back(std::move(points));
          continue;
        }

        if (ColliderEnabled({obj.properties, obj.propertiesLength})) {
          map.points.emplace_back(GetRotatedRectanglePoints(obj));
          continue;
        }

        map.collisions.emplace_back(obj.aabb.x, obj.aabb.y, obj.aabb.width, obj.aabb.height);
      }
    }
  }
}

void World::Draw(const Camera2D *camera) const { DrawTMX(map.tmx_map, camera, nullptr, 0, 0, WHITE); }

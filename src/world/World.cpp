#include "World.h"

#include <algorithm>
#include <iostream>

#include "../third_party/raytmx.h"

#include <array>
#include <cmath>
#include <span>

namespace {
  std::vector<Vector2> GetLocalObjectPoints(const TmxObject &obj) {
    const auto width = static_cast<float>(obj.width);
    const auto height = static_cast<float>(obj.height);

    switch (obj.type) {
      case OBJECT_TYPE_POLYGON:
      case OBJECT_TYPE_POLYLINE: {
        const std::span<const Vector2> objPoints{obj.points, obj.pointsLength};
        return {objPoints.begin(), objPoints.end()};
      }
      case OBJECT_TYPE_TILE:
        return {{0.0f, -height}, {width, -height}, {width, 0.0f}, {0.0f, 0.0f}};
      case OBJECT_TYPE_RECTANGLE:
      case OBJECT_TYPE_ELLIPSE:
      case OBJECT_TYPE_TEXT:
      default:
        return {{0.0f, 0.0f}, {width, 0.0f}, {width, height}, {0.0f, height}};
    }
  }

  // Returns the object's shape as world-space points, rotated around (obj.x, obj.y) by obj.rotation.
  std::vector<Vector2> GetRotatedObjectPoints(const TmxObject &obj) {
    const float radians = static_cast<float>(obj.rotation) * DEG2RAD;
    const float cosine = std::cos(radians);
    const float sine = std::sin(radians);

    const Vector2 origin{static_cast<float>(obj.x), static_cast<float>(obj.y)};
    const std::vector<Vector2> localPoints = GetLocalObjectPoints(obj);

    std::vector<Vector2> points;
    points.reserve(localPoints.size());

    for (const auto &[x, y]: localPoints) {
      points.push_back({origin.x + x * cosine - y * sine, origin.y + x * sine + y * cosine});
    }

    return points;
  }

  void AddCollider(std::vector<MapCollider> &colliders, const TmxObject &obj) {
    if (obj.type == OBJECT_TYPE_POINT) {
      return;
    }

    // Unrotated rectangles can use the pre-computed AABB directly for a cheaper collider.
    // Everything else (including rotated rectangles) needs explicit points.
    if (obj.type == OBJECT_TYPE_RECTANGLE && obj.rotation == 0.0) {
      colliders.emplace_back(MapCollider{.points = {}, .bounds = std::optional(obj.aabb)});
    } else {
      colliders.emplace_back(MapCollider{.points = GetRotatedObjectPoints(obj), .bounds = std::nullopt});
    }
  }
} // namespace

bool ColliderEnabled(std::span<const TmxProperty> properties) {
  return std::ranges::any_of(properties, [](const TmxProperty &property) {
    return property.name != nullptr && std::string_view{property.name} == "collide" &&
           property.type == PROPERTY_TYPE_BOOL && property.boolValue;
  });
}

const TmxObjectGroup *World::FindObjectGroup(const std::string_view name) const {
  const std::span<const TmxLayer> layers{
      map.tmx_map->layers,
      map.tmx_map->layersLength,
  };

  const auto layer = std::ranges::find_if(layers, [name](const TmxLayer &layer) {
    return layer.type == LAYER_TYPE_OBJECT_GROUP && layer.name != nullptr && std::string_view{layer.name} == name;
  });

  if (layer == layers.end()) {
    return nullptr;
  }

  return &layer->exact.objectGroup;
}

void World::LoadCollisions() {
  if (const TmxObjectGroup *group = FindObjectGroup("Colliders")) {
    for (const TmxObject &obj: std::span<const TmxObject>{group->objects, group->objectsLength}) {
      AddCollider(map.colliders, obj);
    }
  }

  if (const TmxObjectGroup *decors = FindObjectGroup("Decorations")) {
    for (const TmxObject &obj: std::span<const TmxObject>{decors->objects, decors->objectsLength}) {
      if (ColliderEnabled({obj.properties, obj.propertiesLength})) {
        AddCollider(map.colliders, obj);
      }
    }
  }
}

void World::LoadMapTransitions() {
  const TmxObjectGroup *group = FindObjectGroup("Transitions");

  if (group == nullptr) {
    return;
  }

  for (const TmxObject &obj: std::span<const TmxObject>{group->objects, group->objectsLength}) {
  }
}

World::World() {
  map = Map{.tmx_map = LoadTMX("../assets/maps/map.tmx"), .grid = BuildGrid{}};
  if (map.tmx_map == nullptr) {
    TraceLog(LOG_ERROR, "Could not load map");
  }

  // Width and height from tmx map are actually number of tiles not pixels
  map.width = map.tmx_map->width * 16;
  map.height = map.tmx_map->height * 16;

  LoadCollisions();
  LoadMapTransitions();
}

void World::Draw(const Camera2D *camera) const { DrawTMX(map.tmx_map, camera, nullptr, 0, 0, WHITE); }

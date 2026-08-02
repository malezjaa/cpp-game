#include "DevTools.h"

#include <span>

#include "../world/World.h"
#include "../world/collisions.h"
#include "raylib.h"
namespace {
  void DrawColliderPoints(const std::vector<MapCollider> &colliders, Color color,
                          const std::optional<std::string> &text = std::nullopt) {
    constexpr float line_thickness = 0.5f;
    constexpr float font_size = 6.0f;
    constexpr float text_spacing = 0.5f;
    constexpr float text_margin = 2.0f;

    const Font font = GetFontDefault();

    for (const auto &[points, obj_bounds]: colliders) {
      std::optional<Rectangle> label_bounds = obj_bounds;

      if (obj_bounds) {
        DrawRectangleLinesEx(*obj_bounds, line_thickness, color);
      } else {
        if (points.size() < 2) {
          continue;
        }

        DrawLineStrip(points.data(), static_cast<int>(points.size()), color);
        DrawLineV(points.back(), points.front(), color);

        float min_x = points.front().x;
        float min_y = points.front().y;
        float max_x = points.front().x;
        float max_y = points.front().y;

        for (const Vector2 point: points) {
          min_x = std::min(min_x, point.x);
          min_y = std::min(min_y, point.y);
          max_x = std::max(max_x, point.x);
          max_y = std::max(max_y, point.y);
        }

        label_bounds = Rectangle{
            min_x,
            min_y,
            max_x - min_x,
            max_y - min_y,
        };
      }

      if (text && label_bounds) {
        const Vector2 text_size = MeasureTextEx(font, text->c_str(), font_size, text_spacing);

        const Vector2 text_position{
            label_bounds->x + (label_bounds->width - text_size.x) / 2.0f,
            label_bounds->y - text_size.y - text_margin,
        };

        DrawTextEx(font, text->c_str(), text_position, font_size, text_spacing, color);
      }
    }
  }
} // namespace

void DevTools::DrawColliderBounds(const World &world, const entt::registry &registry) const {
  if (!settings.draw_colliders) {
    return;
  }

  DrawColliderPoints(world.GetMap().colliders, ORANGE);

  for (const auto &collider: registry.view<Collider, Position>()) {
    const auto &pos = registry.get<Position>(collider);
    const auto &col = registry.get<Collider>(collider);

    Rectangle bounds = GetBounds(pos, col);

    bounds.x = std::round(bounds.x);
    bounds.y = std::round(bounds.y);
    bounds.width = std::round(bounds.width);
    bounds.height = std::round(bounds.height);

    DrawRectangleLinesEx(bounds, .5f, ORANGE);
  }
}

void DevTools::DrawGridMap(const World &world) const {
  if (settings.draw_grid_map) {
    for (int x = 0; x <= world.GetMap().width; x += 16) {
      DrawLine(x, 0, x, static_cast<int>(world.GetMap().height), BLUE);
    }

    for (int y = 0; y <= world.GetMap().height; y += 16) {
      DrawLine(0, y, static_cast<int>(world.GetMap().width), y, BLUE);
    }
  }
}

void DevTools::DrawMapTransitions(const World &world) const {
  if (settings.draw_map_transitions) {
    for (const auto &transition: world.GetMap().transitions) {
      DrawColliderPoints(transition.transition_points, RED, transition.map_id);
    }
  }
}

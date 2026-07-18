#include "Hotbar.h"

#include <algorithm>
#include <iostream>
#include <ranges>

using std::ranges::views::iota;

Hotbar::Hotbar(const Textures &textures) : textures(textures) {
  for (int i: iota(1, 10)) {
    slots.emplace_back(i);
  }
}

constexpr float SLOT_SIZE_PERCENT = 8.0f; // in percents
constexpr float BORDER_THICKNESS = 3.0f;

void Hotbar::Draw() {
  const auto screen_width = static_cast<float>(GetScreenWidth());
  const auto screen_height = static_cast<float>(GetScreenHeight());
  const auto slot_count = static_cast<float>(slots.size());

  const float reference_size = std::min(screen_width, screen_height);

  const float slot_size = std::clamp(reference_size * 0.10f, 48.0f, 80.0f);
  const float border_thickness = std::clamp(slot_size * 0.04f, 2.0f, 4.0f);

  const float container_width = slot_size * slot_count - border_thickness * (slot_count - 1.0f);
  const float container_x = (screen_width - container_width) / 2.0f;
  const float container_y = screen_height - slot_size - 5.0f;

  const float corner_inset = slot_size * 0.12f;

  const Rectangle hotbar_background{
      container_x + corner_inset,
      container_y,
      container_width - corner_inset * 2.0f,
      slot_size,
  };

  DrawRectangleRec(hotbar_background, Color{90, 90, 90, 255});

  float slot_x = container_x;

  for (const auto &slot: slots) {
    const Rectangle rect{
        slot_x,
        container_y,
        slot_size,
        slot_size,
    };

    DrawTexturePro(textures.Tiles(), Textures::INVENTORY_SLOT_RECT, rect, Vector2{0.0f, 0.0f}, 0.0f, WHITE);

    slot_x += slot_size - BORDER_THICKNESS;
  }
}

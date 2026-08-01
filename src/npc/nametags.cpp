#include "nametags.h"

#include "../animations.h"
#include "../ecs/components.h"
#include "../ui/TextRenderer.h"
#include "../ui/UIManager.h"
#include "Npc.h"

void DrawNameTags(entt::registry &registry, const TextRenderer &text_renderer) {
  const float scale = UIManager::Scale();
  const float text_size = 3.5f * scale;
  const float spacing = 0.3f;

  const Vector2 padding{
      1.0f * scale,
      0.5f * scale,
  };

  for (const auto &entity: registry.view<AnimatedSprite, Position, NpcEntity>()) {
    auto &[pos] = registry.get<Position>(entity);
    auto sprite_size = GetSpriteSize(registry.get<AnimatedSprite>(entity));
    const auto &[name] = GetNpcDefinition(registry.get<NpcEntity>(entity).id);
    auto npc_name = std::string(name);

    const auto [text_width, text_height] = text_renderer.Measure(npc_name, text_size, spacing);
    const Vector2 text_position = {pos.x - (text_width / 2) + sprite_size.x / 2, pos.y + text_height - sprite_size.y};

    const Rectangle background{
        text_position.x - padding.x,
        text_position.y - padding.y,
        text_width + padding.x * 2.0f,
        text_height + padding.y * 2.0f,
    };

    DrawRectangleRec(background, Fade(BLACK, 0.5f));
    text_renderer.Render(npc_name, text_position, text_size, WHITE, spacing);
  }
};

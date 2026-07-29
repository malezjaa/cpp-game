#include "HealthBar.h"

#include <format>

#include "../Textures.h"
#include "../ecs/Components.h"
#include "UIManager.h"

void DrawHealthBar(const TextRenderer &text_renderer, const Textures &textures, const Health &health) {
  const float uiScale = UIManager::Scale();
  const float textureScale = uiScale * 2.0f;

  const auto &hpTexture = textures.HP();
  const auto &barTexture = textures.HPBar();

  const auto hpWidth = static_cast<float>(hpTexture.GetWidth());
  const auto hpHeight = static_cast<float>(hpTexture.GetHeight());

  const Vector2 barPosition{
      10.0f * uiScale,
      10.0f * uiScale,
  };

  const Vector2 hpOffset{
      10.0f * textureScale,
      4.0f * textureScale,
  };

  const float healthRatio =
      std::clamp(static_cast<float>(health.current) / static_cast<float>(health.maximum), 0.0f, 1.0f);

  const Rectangle hpSource{
      0.0f,
      0.0f,
      hpWidth * healthRatio,
      hpHeight,
  };

  const Rectangle hpDestination{
      barPosition.x + hpOffset.x,
      barPosition.y + hpOffset.y,
      hpWidth * textureScale * healthRatio,
      hpHeight * textureScale,
  };

  DrawRectanglePro(
      {
          barPosition.x + hpOffset.x,
          barPosition.y + hpOffset.y,
          hpWidth * textureScale,
          hpHeight * textureScale,
      },
      {0.0f, 0.0f}, 0.0f, DARKGRAY);

  DrawTexturePro(hpTexture, hpSource, hpDestination, {0.0f, 0.0f}, 0.0f, WHITE);
  DrawTextureEx(barTexture, barPosition, 0.0f, textureScale, WHITE);

  const auto health_text = std::format("{} / {}", health.current, health.maximum);

  const float spacing = UIManager::Scale();
  const float fontSize = 6.0f * spacing;

  const auto [text_x, text_y] = text_renderer.Measure(health_text, fontSize, spacing);

  const Vector2 textPosition{
      barPosition.x + hpOffset.x + (hpWidth * textureScale - text_x) / 2.0f,
      barPosition.y + hpOffset.y + (hpHeight * textureScale - text_y) / 2.0f + 1.0f,
  };

  text_renderer.Render(health_text, {textPosition.x + spacing, textPosition.y + spacing}, fontSize, BLACK, spacing);
  text_renderer.Render(health_text, textPosition, fontSize, WHITE, spacing);
}

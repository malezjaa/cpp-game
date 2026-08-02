#ifndef INC_2D_GAME_TMX_PROPERTIES_H
#define INC_2D_GAME_TMX_PROPERTIES_H
#include <optional>
#include <span>
#include <string_view>

#include "../third_party/raytmx.h"

bool PropertyEnabled(std::span<const TmxProperty> properties, std::string_view property_name);
std::optional<std::string_view> GetStringProperty(std::span<const TmxProperty> properties,
                                                  std::string_view property_name);
#endif

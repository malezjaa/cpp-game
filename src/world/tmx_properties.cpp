#include "tmx_properties.h"

#include <algorithm>
#include <expected>
#include <span>
#include <string>
#include <string_view>

#include "../third_party/raytmx.h"

bool PropertyEnabled(std::span<const TmxProperty> properties, std::string_view property_name) {
  return std::ranges::any_of(properties, [property_name](const TmxProperty &property) {
    return property.name != nullptr && std::string_view{property.name} == property_name &&
           property.type == PROPERTY_TYPE_BOOL && property.boolValue;
  });
}

std::optional<std::string_view> GetStringProperty(const std::span<const TmxProperty> properties,
                                                  const std::string_view property_name) {
  for (const TmxProperty &property: properties) {
    if (property.name == nullptr || property.stringValue == nullptr || property.type != PROPERTY_TYPE_STRING ||
        std::string_view{property.name} != property_name) {
      continue;
    }

    return std::string_view{property.stringValue};
  }

  return std::nullopt;
}

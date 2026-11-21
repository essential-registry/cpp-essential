#include "essential/greeting.hpp"

#include <algorithm>
#include <cctype>
#include <format>

namespace essential {

namespace {
bool is_blank(std::string_view text) {
  return std::ranges::all_of(text, [](unsigned char c) { return std::isspace(c) != 0; });
}
}  // namespace

std::expected<std::string, Error> greet(std::string_view name, std::string_view app_name) {
  if (is_blank(name)) {
    return std::unexpected(Error{ErrorCode::InvalidInput, "name must not be empty"});
  }
  return std::format("Hello, {}! Welcome to {}.", name, app_name);
}

}  // namespace essential

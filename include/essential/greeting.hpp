#pragma once

#include <expected>
#include <string>
#include <string_view>

#include "essential/error.hpp"

namespace essential {

/// Build a greeting for `name`, signed by `app_name`.
/// Returns `InvalidInput` when `name` is empty or only whitespace.
[[nodiscard]] std::expected<std::string, Error> greet(std::string_view name,
                                                      std::string_view app_name);

}  // namespace essential

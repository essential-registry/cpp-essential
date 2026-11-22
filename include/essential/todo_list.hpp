#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <vector>

#include "essential/error.hpp"

namespace essential {

struct Todo {
  std::uint32_t id = 0;
  std::string title;
  bool done = false;
};

/// An in-memory todo list. Owns its items; copy and move work as for any value type.
class TodoList {
 public:
  /// Add a todo and return its id (ids start at 1).
  [[nodiscard]] std::expected<std::uint32_t, Error> add(std::string_view title);

  /// Mark a todo as done. Returns `NotFound` for an unknown id.
  [[nodiscard]] std::expected<void, Error> complete(std::uint32_t id);

  [[nodiscard]] const std::vector<Todo>& items() const noexcept { return items_; }

 private:
  std::vector<Todo> items_;
  std::uint32_t next_id_ = 1;
};

}  // namespace essential

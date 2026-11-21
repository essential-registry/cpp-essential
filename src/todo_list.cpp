#include "essential/todo_list.hpp"

#include <algorithm>
#include <format>

namespace essential {

std::expected<std::uint32_t, Error> TodoList::add(std::string_view title) {
  if (title.empty()) {
    return std::unexpected(Error{ErrorCode::InvalidInput, "title must not be empty"});
  }
  const std::uint32_t id = next_id_++;
  items_.push_back(Todo{id, std::string{title}, false});
  return id;
}

std::expected<void, Error> TodoList::complete(std::uint32_t id) {
  const auto found = std::ranges::find(items_, id, &Todo::id);
  if (found == items_.end()) {
    return std::unexpected(Error{ErrorCode::NotFound, std::format("todo {} not found", id)});
  }
  found->done = true;
  return {};
}

}  // namespace essential

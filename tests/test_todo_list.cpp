#include <catch2/catch_test_macros.hpp>

#include "essential/todo_list.hpp"

TEST_CASE("todo ids start at one and increase") {
  essential::TodoList list;
  CHECK(list.add("a") == 1U);
  CHECK(list.add("b") == 2U);
}

TEST_CASE("completing marks the todo done") {
  essential::TodoList list;
  const auto id = list.add("write docs");
  REQUIRE(id.has_value());
  REQUIRE(list.complete(*id).has_value());
  CHECK(list.items().front().done);
}

TEST_CASE("completing an unknown id fails") {
  essential::TodoList list;
  const auto result = list.complete(9);
  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().code == essential::ErrorCode::NotFound);
}

TEST_CASE("empty titles are rejected") {
  essential::TodoList list;
  CHECK_FALSE(list.add("").has_value());
}

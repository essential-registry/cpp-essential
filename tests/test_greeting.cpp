#include <catch2/catch_test_macros.hpp>

#include "essential/greeting.hpp"

TEST_CASE("greet builds a greeting") {
  const auto result = essential::greet("Ada", "Essential");
  REQUIRE(result.has_value());
  CHECK(*result == "Hello, Ada! Welcome to Essential.");
}

TEST_CASE("greet rejects blank names") {
  const auto result = essential::greet("  ", "Essential");
  REQUIRE_FALSE(result.has_value());
  CHECK(result.error().code == essential::ErrorCode::InvalidInput);
}

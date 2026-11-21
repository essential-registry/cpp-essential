#pragma once

#include <cstdint>
#include <string>

namespace essential {

/// What went wrong. Errors are values: functions return `std::expected<T, Error>`.
enum class ErrorCode : std::uint8_t { InvalidInput, NotFound };

struct Error {
  ErrorCode code;
  std::string message;

  friend bool operator==(const Error&, const Error&) = default;
};

}  // namespace essential

# 3. Errors and ownership

## Errors are values

Functions that can fail return `std::expected<T, essential::Error>`; `Error` carries an `ErrorCode` and a message. Callers check the result, never catch. `[[nodiscard]]` stops results being ignored.

```cpp
const auto greeting = essential::greet(name, "App");
if (!greeting) { std::cerr << greeting.error().message << "\n"; return 1; }
```

Exceptions are for truly exceptional failures (out of memory). `main` catches everything so none escape (`bugprone-exception-escape` enforces this).

## Ownership

- Resources are owned by objects (RAII): `std::string`, `std::vector`, `std::unique_ptr`. No `new`/`delete` in application code.
- Pass cheap-to-copy types by value, others by `const&`, views by `std::string_view` / `std::span`. A raw pointer or reference never owns.
- In C, every pointer parameter documents nullability, ownership and size; the caller owns buffers it passes in. Use bounded functions (`memcpy` with explicit sizes, `snprintf`).

#include <format>
#include <iostream>
#include <string_view>

#include "essential/greeting.hpp"
#include "essential/todo_list.hpp"

namespace {

// std::print needs GCC 14; iostream + std::format builds on GCC 13 and newer, and on Clang.
void out(std::string_view text) {
  std::cout << text << '\n';
}
void err(std::string_view text) {
  std::cerr << text << '\n';
}

int run_greet(std::string_view name) {
  const auto greeting = essential::greet(name, "C++ Essential");
  if (!greeting) {
    err(std::format("error: {}", greeting.error().message));
    return 1;
  }
  out(*greeting);
  return 0;
}

int run_todo() {
  essential::TodoList list;
  const auto id = list.add("ship the template");
  if (!id || !list.complete(*id)) {
    return 1;
  }
  for (const auto& todo : list.items()) {
    out(std::format("[{}] {} {}", todo.done ? 'x' : ' ', todo.id, todo.title));
  }
  return 0;
}

}  // namespace

namespace {

int dispatch(int argc, const char* const* argv) {
  if (argc >= 3 && std::string_view{argv[1]} == "greet") {
    return run_greet(argv[2]);
  }
  if (argc == 2 && std::string_view{argv[1]} == "todo") {
    return run_todo();
  }
  err("usage: essential greet <name> | essential todo");
  return 2;
}

}  // namespace

// main must not let exceptions escape (formatting and IO can throw).
// NOLINTNEXTLINE(misc-const-correctness): the signature of main is fixed by the standard
int main(int argc, char** argv) {
  try {
    return dispatch(argc, argv);
  } catch (...) {
    return 1;
  }
}

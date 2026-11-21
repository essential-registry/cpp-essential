#include <print>
#include <string_view>

#include "essential/greeting.hpp"
#include "essential/todo_list.hpp"

namespace {

int run_greet(std::string_view name) {
  const auto greeting = essential::greet(name, "C++ Essential");
  if (!greeting) {
    std::println(stderr, "error: {}", greeting.error().message);
    return 1;
  }
  std::println("{}", *greeting);
  return 0;
}

int run_todo() {
  essential::TodoList list;
  const auto id = list.add("ship the template");
  if (!id || !list.complete(*id)) {
    return 1;
  }
  for (const auto& todo : list.items()) {
    std::println("[{}] {} {}", todo.done ? 'x' : ' ', todo.id, todo.title);
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
  std::println(stderr, "usage: essential greet <name> | essential todo");
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

# -DESSENTIAL_SANITIZE=address;undefined  (or thread). Applies to every target.
set(ESSENTIAL_SANITIZE "" CACHE STRING "Sanitizers to enable, e.g. address;undefined or thread")

if(ESSENTIAL_SANITIZE AND NOT MSVC)
  string(REPLACE ";" "," _essential_san "${ESSENTIAL_SANITIZE}")
  add_compile_options(-fsanitize=${_essential_san} -fno-omit-frame-pointer)
  add_link_options(-fsanitize=${_essential_san})
endif()

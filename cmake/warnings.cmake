# essential_enable_warnings(<target>): strict warnings, errors when ESSENTIAL_WERROR is ON.
option(ESSENTIAL_WERROR "Treat warnings as errors" OFF)

function(essential_enable_warnings target)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 $<$<BOOL:${ESSENTIAL_WERROR}>:/WX>)
  else()
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion
      $<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>
      $<$<COMPILE_LANGUAGE:CXX>:-Wnon-virtual-dtor>
      $<$<BOOL:${ESSENTIAL_WERROR}>:-Werror>)
  endif()
endfunction()

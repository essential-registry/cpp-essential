add_library(essential_c STATIC src/strutil.c)
add_library(essential::c ALIAS essential_c)
target_include_directories(essential_c PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
essential_enable_warnings(essential_c)

if(BUILD_TESTING)
  add_executable(essential_c_tests tests/test_strutil.c)
  target_link_libraries(essential_c_tests PRIVATE essential::c)
  essential_enable_warnings(essential_c_tests)
  add_test(NAME essential_c_tests COMMAND essential_c_tests)
endif()

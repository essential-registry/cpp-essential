# Test dependency. Prefers vcpkg (manifest mode, vcpkg.json); falls back to FetchContent
# so the project builds without vcpkg installed.
find_package(Catch2 3 CONFIG QUIET)
if(NOT Catch2_FOUND)
  include(FetchContent)
  FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
    GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(Catch2)
  list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
endif()
include(Catch)

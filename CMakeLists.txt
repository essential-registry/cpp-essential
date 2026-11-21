cmake_minimum_required(VERSION 3.28)

project(essential
  VERSION 0.1.0
  DESCRIPTION "C++23 and C17 starter with the essentials"
  LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Keep one language: -DESSENTIAL_LANGS="CXX" or "C" (docs/01-architecture.md). Default: both.
set(ESSENTIAL_LANGS "C;CXX" CACHE STRING "Languages to build: C, CXX or C;CXX")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(CTest)
include(warnings)
include(sanitizers)

if("CXX" IN_LIST ESSENTIAL_LANGS)
  add_subdirectory(src)
  add_subdirectory(apps/cli)
  if(BUILD_TESTING)
    include(deps)
    add_subdirectory(tests)
  endif()
endif()

if("C" IN_LIST ESSENTIAL_LANGS)
  add_subdirectory(c)
endif()

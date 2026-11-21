---
name: add-dependency
description: Add a third-party library through vcpkg.
---

Add it to `vcpkg.json`, `find_package(<pkg> CONFIG REQUIRED)` in the right CMake file, link the imported target, and build with a `*-vcpkg` preset (`export VCPKG_ROOT=...`). Ask before adding a dependency.

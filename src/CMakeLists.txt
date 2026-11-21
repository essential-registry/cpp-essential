add_library(essential STATIC greeting.cpp todo_list.cpp)
add_library(essential::essential ALIAS essential)
target_include_directories(essential PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(essential PUBLIC cxx_std_23)
essential_enable_warnings(essential)

include(GNUInstallDirs)
install(TARGETS essential EXPORT essentialTargets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT essentialTargets NAMESPACE essential:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/essential)

cmake_minimum_required(VERSION 3.21)

project(BetterVinaUI LANGUAGES CXX RC)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(vina_compile_options INTERFACE)
target_compile_definitions(vina_compile_options INTERFACE UNICODE _UNICODE)
target_compile_options(vina_compile_options INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
  $<$<CXX_COMPILER_ID:MSVC>:/permissive>
  $<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->
  $<$<CXX_COMPILER_ID:MSVC>:/wd4828>
  $<$<CXX_COMPILER_ID:MSVC>:/WX->
)

add_library(vina_framework_headers INTERFACE)
target_include_directories(vina_framework_headers INTERFACE
  framework
  framework/Vina
)

add_library(vina_vertexui_headers INTERFACE)
target_include_directories(vina_vertexui_headers INTERFACE
  framework/VertexUI
)

add_library(vina_parser_headers INTERFACE)
target_include_directories(vina_parser_headers INTERFACE
  framework/VertexUI/vui.parser
)

add_library(vina_third_party_headers INTERFACE)
target_include_directories(vina_third_party_headers INTERFACE
  third_party
)

add_library(vina_win32_libs INTERFACE)
target_link_libraries(vina_win32_libs INTERFACE
  d2d1
  dwrite
  windowscodecs
  imm32
  shell32
  ole32
  shlwapi
  msimg32
  gdiplus
  user32
  gdi32
  comdlg32
  advapi32
)

add_library(vina_sdk INTERFACE)
add_library(VinaUI::SDK ALIAS vina_sdk)

target_compile_definitions(vina_sdk INTERFACE UNICODE _UNICODE)
target_compile_options(vina_sdk INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
  $<$<CXX_COMPILER_ID:MSVC>:/permissive>
  $<$<CXX_COMPILER_ID:MSVC>:/Zc:strictStrings->
  $<$<CXX_COMPILER_ID:MSVC>:/wd4828>
  $<$<CXX_COMPILER_ID:MSVC>:/WX->
)

target_include_directories(vina_sdk INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/framework>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/framework/Vina>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/framework/VertexUI>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Vina>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/VertexUI>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/third_party>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/third_party/tsl>
)

target_link_libraries(vina_sdk INTERFACE
  d2d1
  dwrite
  windowscodecs
  imm32
  shell32
  ole32
  shlwapi
  msimg32
  gdiplus
  user32
  gdi32
  comdlg32
  advapi32
)

add_executable(vina_demo WIN32
  apps/vina-demo/src/VinaApp.cpp
  apps/vina-demo/resources/VinaApp.rc
)

target_include_directories(vina_demo PRIVATE
  apps/vina-demo/src
  apps/vina-demo/resources
)

target_link_libraries(vina_demo PRIVATE
  vina_sdk
)

option(BUILD_VUI_PARSER_CLI "Build vui.parser command line demo target" OFF)

if(BUILD_VUI_PARSER_CLI)
  add_executable(vui_parser_cli
    framework/VertexUI/vui.parser/main.cpp
  )

  target_link_libraries(vui_parser_cli PRIVATE
    vina_compile_options
    vina_parser_headers
  )
endif()

set(VINAUI_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/VinaUI")

install(TARGETS vina_sdk EXPORT VinaUITargets)

install(
  DIRECTORY framework/Vina/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Vina
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
install(
  DIRECTORY framework/VertexUI/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/VertexUI
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
install(
  DIRECTORY third_party/tsl/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/third_party/tsl
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
install(
  FILES framework/LightFrame.WindowAnimation.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  DIRECTORY assets/
  DESTINATION ${CMAKE_INSTALL_DATADIR}/vinaui/assets
)
install(
  FILES README.md LICENSE.txt
  DESTINATION ${CMAKE_INSTALL_DATADIR}/vinaui
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/VinaUIConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/VinaUIConfig.cmake
  INSTALL_DESTINATION ${VINAUI_INSTALL_CMAKEDIR}
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/VinaUIConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
)

install(
  EXPORT VinaUITargets
  FILE VinaUITargets.cmake
  NAMESPACE VinaUI::
  DESTINATION ${VINAUI_INSTALL_CMAKEDIR}
)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/VinaUIConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/VinaUIConfigVersion.cmake
  DESTINATION ${VINAUI_INSTALL_CMAKEDIR}
)

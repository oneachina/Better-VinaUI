cmake_minimum_required(VERSION 3.21)

project(BetterVinaUI LANGUAGES CXX RC)

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

add_executable(vina_demo WIN32
  apps/vina-demo/src/VinaApp.cpp
  apps/vina-demo/resources/VinaApp.rc
)

target_include_directories(vina_demo PRIVATE
  apps/vina-demo/src
  apps/vina-demo/resources
)

target_link_libraries(vina_demo PRIVATE
  vina_compile_options
  vina_framework_headers
  vina_vertexui_headers
  vina_third_party_headers
  vina_win32_libs
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

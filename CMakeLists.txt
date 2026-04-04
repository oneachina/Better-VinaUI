cmake_minimum_required(VERSION 3.21)

project(BetterVinaUI LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(vina_demo WIN32
  apps/vina-demo/src/VinaApp.cpp
  apps/vina-demo/resources/VinaApp.rc
)

target_include_directories(vina_demo PRIVATE
  apps/vina-demo/src
  apps/vina-demo/resources
  framework
  framework/Vina
  framework/VertexUI
  third_party
)

target_compile_definitions(vina_demo PRIVATE UNICODE _UNICODE)

if(MSVC)
  target_compile_options(vina_demo PRIVATE /utf-8 /permissive /Zc:strictStrings- /wd4828 /WX-)
endif()

target_link_libraries(vina_demo PRIVATE
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

option(BUILD_VUI_PARSER_CLI "Build vui.parser command line demo target" OFF)

if(BUILD_VUI_PARSER_CLI)
  add_executable(vui_parser_cli
    framework/VertexUI/vui.parser/main.cpp
  )

  target_include_directories(vui_parser_cli PRIVATE
    framework/VertexUI
    framework/VertexUI/vui.parser
  )

  target_compile_definitions(vui_parser_cli PRIVATE UNICODE _UNICODE)

  if(MSVC)
    target_compile_options(vui_parser_cli PRIVATE /utf-8 /permissive /Zc:strictStrings- /wd4828 /WX-)
  endif()
endif()

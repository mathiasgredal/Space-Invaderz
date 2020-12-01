cmake_minimum_required(VERSION 3.5)

project(Space-Invaderz LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Do static compiles
set(BUILD_SHARED_LIBS OFF)

# Add relevant packages
include(cmake/CPM.cmake)
CPMAddPackage(
  NAME SFML
  URL "https://github.com/SFML/SFML/archive/2.5.1.zip"
  VERSION 2.5.1
)

CPMAddPackage(
  NAME imgui
  URL "https://github.com/ocornut/imgui/archive/v1.68.zip"
  VERSION 1.68
)

set(IMGUI_ROOT ${imgui_SOURCE_DIR})
include_directories(${imgui_SOURCE_DIR})
set(IMGUI_SOURCES
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

CPMAddPackage(
  NAME imgui-sfml
  GITHUB_REPOSITORY eliasdaler/imgui-sfml
  GIT_TAG        5f54b69b6aee18db846c81633f86f78c2586dded
)

# Add resource files
include(cmake/CMakeRC.cmake)
# cmrc_add_resource_library(assets_fonts ALIAS Assets::Fonts NAMESPACE Assets "./Assets/FreeSerif.ttf")
cmrc_add_resource_library(assets_sprites ALIAS Assets::Sprites NAMESPACE Assets "./Assets/sprites.png")


add_executable(Space-Invaderz main.cpp
    src/game.cpp src/game.h
    src/player.cpp src/player.h
    src/bullet.cpp src/bullet.h
    src/alien.cpp src/alien.h
    src/shield.cpp src/shield.h
    src/utility.cpp src/utility.h
    )
target_link_libraries(Space-Invaderz PUBLIC ImGui-SFML::ImGui-SFML Assets::Sprites)

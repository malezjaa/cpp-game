cmake_minimum_required(VERSION 3.14)
project(2d_game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 6.0
            GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif ()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v6.0.0)
    endif ()
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif ()

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.7
        GIT_SHALLOW TRUE
)

# raylib backend for Dear ImGui
FetchContent_Declare(
        rlimgui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG Raylib_6_0
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui rlimgui)

FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG v0.9.8
)

FetchContent_MakeAvailable(magic_enum)

find_package(EnTT CONFIG REQUIRED)

set(SOURCES src/main.cpp
        src/Player.cpp
        src/Player.h
        src/scenes/Game.cpp
        src/scenes/Game.h
        src/Hotbar.cpp
        src/Hotbar.h
        src/items/Item.cpp
        src/items/Item.h
        src/Textures.h
        src/Textures.cpp
        src/items/ItemRegistry.cpp
        src/items/ItemRegistry.h
        src/utils.cpp
        src/utils.h
        src/ecs/Components.h
        src/ecs/systems.cpp
        src/ecs/systems.h
        src/scenes/SceneManager.cpp
        src/scenes/SceneManager.h
        src/scenes/MainMenu.cpp
        src/scenes/MainMenu.h
        src/ui/TextRenderer.h
        src/ui/NineSlice.h
        src/ui/UIManager.h
        src/scenes/Credits.h
        src/world/World.h
        src/world/map.h
        src/world/tiles.h
        src/world/World.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui
        PUBLIC
        ${imgui_SOURCE_DIR}
)

add_library(rlimgui STATIC
        ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)

target_include_directories(rlimgui
        PUBLIC
        ${rlimgui_SOURCE_DIR}
)

target_link_libraries(rlimgui
        PUBLIC
        imgui
        raylib
)

target_link_libraries(2d_game PRIVATE
        raylib
        raylib_cpp
        EnTT::EnTT
        rlimgui
        magic_enum::magic_enum
)
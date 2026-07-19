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
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp EnTT::EnTT)
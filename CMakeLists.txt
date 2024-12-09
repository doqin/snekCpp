cmake_minimum_required(VERSION 3.30)
project(snekCpp)

set(CMAKE_CXX_STANDARD 23)

set(INCLUDE ./core/src/class)

include_directories(${INCLUDE})

add_executable(${PROJECT_NAME}
        core/src/main/main.cpp
        core/src/class/game.h
        core/src/class/state.h
        core/src/class/engine.h
        core/src/class/engine.cpp
        core/src/class/snekCpp.h
        core/src/class/MainMenuScreen.h
        core/src/class/MainMenuScreen.cpp
        core/src/class/LTexture.h
        core/src/class/LTexture.cpp
        core/src/class/GameScreen.h
)

#find libraries and packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
target_include_directories(${PROJECT_NAME}
        PUBLIC ${SDL2_INCLUDE_DIRS}
        PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
        PUBLIC ${SDL2MIXER_INCLUDE_DIRS}
        PUBLIC ${SDL2TTF_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
)

#enable compile command export
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


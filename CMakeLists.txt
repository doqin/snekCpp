cmake_minimum_required(VERSION 3.30)
project(snekCpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        core/src/main/c++/main.cpp
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


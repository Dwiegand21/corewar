
cmake_minimum_required(VERSION 3.14)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/external/cmake_modules/sdl2)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_gfx REQUIRED)
#


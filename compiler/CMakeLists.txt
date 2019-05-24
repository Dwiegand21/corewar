cmake_minimum_required(VERSION 3.14)
project(asm C)

set(CMAKE_C_STANDARD 99)

find_library(OPEN_GL OpenGl)
find_library(APP_KIT AppKit)
link_libraries(mlx)

add_compile_options(-Wall -Wextra)

include_directories(./libft/includes)
FILE(GLOB LIBFT_SRCS ./libft/*.c ./libft/*/*.c)

add_executable(asm srcs/main.c ${LIBFT_SRCS})

target_link_libraries(asm ${OPEN_GL} ${APP_KIT})
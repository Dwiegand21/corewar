
cmake_minimum_required(VERSION 2.9)

project(libft C)

include_directories(includes)

FILE(GLOB LIB_FILES
        sources/ft_iostream/*.c
        sources/ft_list/*.c
        sources/ft_matrix/*.c
        sources/ft_memory/*.c
        sources/ft_queue/*.c
        sources/ft_stack/*.c
        sources/ft_string/*.c
        sources/ft_project_assets/*.c
        sources/ft_vector/*.c)

add_library(ft STATIC ${LIB_FILES})
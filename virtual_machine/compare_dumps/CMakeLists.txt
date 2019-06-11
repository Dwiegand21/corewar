cmake_minimum_required(VERSION 3.0)

project(dump_diff)

set(EXE_FILES sources/main.c
        sources/read_processes_output.c
        sources/diff_output.c
        )

include_directories(includes
                   ../libft/includes)

add_executable(dumpcmp ${EXE_FILES})

cmake_minimum_required(VERSION 3.0)

project(dump_diff)

set(EXE_FILES sources/dump_diff.c
        sources/read_processes_output.c
        sources/diff_output.c
        sources/helpers.c)

include_directories(includes)

add_executable(dump_diff ${EXE_FILES})

cmake_minimum_required(VERSION 3.10)

project( libft C )
set( CMAKE_C_STANDARD 11 )

set( _LIB_SRC_DEF ON )
set( LIB_SRC "" )

set( SrcDirPathsList
        ${PROJECT_SOURCE_DIR}/sources/ft_binary_heap/
        ${PROJECT_SOURCE_DIR}/sources/ft_iostream/
        ${PROJECT_SOURCE_DIR}/sources/ft_list/
        ${PROJECT_SOURCE_DIR}/sources/ft_matrix/
        ${PROJECT_SOURCE_DIR}/sources/ft_memory/
        ${PROJECT_SOURCE_DIR}/sources/ft_printf/
        ${PROJECT_SOURCE_DIR}/sources/ft_project_assets/
        ${PROJECT_SOURCE_DIR}/sources/ft_string/
        ${PROJECT_SOURCE_DIR}/sources/ft_vector/
        )

foreach( SrcDirPath IN ITEMS ${SrcDirPathsList} )
    include( ${SrcDirPath}AppendSrcFiles.cmake )
endforeach()


set( TARGET ft )

add_library( ${TARGET} STATIC ${LIB_SRC})

target_include_directories( ${TARGET} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes

        )

set_target_properties( ${TARGET} PROPERTIES
        C_STANDART 11
        C_STANDART_REQUIRED ON
        )

target_compile_options( ${TARGET} PRIVATE
        -Wall
        -Wextra
        -Werror
        )

target_compile_options( ${TARGET} PRIVATE
        -O2
        -march=native
        -Wshadow
        -Wundef
        -Wstrict-prototypes
        -Wno-unused-result
        -D_FORTIFY_SOURCE=2
        )





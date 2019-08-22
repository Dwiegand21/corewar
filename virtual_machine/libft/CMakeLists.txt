
cmake_minimum_required(VERSION 3.10)

project( libft C )
set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_FLAGS "-Wall -Wextra -Werror" )

set( _LIB_SRC_DEF ON )
set( LIB_SRC "" )

set( TARGET ft )

set( SrcDirPathsList
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_binary_heap/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_iostream/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_list/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_matrix/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_memory/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_printf/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_project_assets/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_string/
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_vector/
        )
include(${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_printf/AppendSrcFiles.cmake)

foreach( SrcDirPath IN ITEMS ${SrcDirPathsList} )
    include( ${SrcDirPath}AppendSrcFiles.cmake )
endforeach()

#
#list( APPEND LIB_SRC ${LIB_FILES} )


add_library( ${TARGET} STATIC ${LIB_SRC})

target_include_directories( ${TARGET} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        )

set_target_properties( ${TARGET} PROPERTIES
        C_STANDART 99
        C_STANDART_REQUIRED ON
        )

target_compile_options( ${TARGET} PRIVATE ${BUILD_FLAGS} )
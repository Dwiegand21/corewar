
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_matrix/"
        )

set( SourceFiles
        ft_matrix.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
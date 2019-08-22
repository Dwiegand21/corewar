
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_memory/"
        )

set( SourceFiles
        ft_bzero.c
        ft_memalloc.c
        ft_memccpy.c
        ft_memchr.c
        ft_memclear_n_del.c
        ft_memcmp.c
        ft_memcpy.c
        ft_memdel.c
        ft_memmove.c
        ft_memset.c
        ft_realloc.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
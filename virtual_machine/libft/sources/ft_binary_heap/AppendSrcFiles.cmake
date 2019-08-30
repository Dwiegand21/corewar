
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_binary_heap/"
        )

set( SourceFiles
        ft_bheap_extract.c
        ft_bheap_get.c
        ft_bheap_init.c
        ft_bheap_insert.c
        ft_bheap_sift_down.c
        ft_bheap_tools.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
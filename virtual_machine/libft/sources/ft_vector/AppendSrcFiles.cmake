
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_vector/"
        )

set( SourceFiles
        ft_vector_begin.c
        ft_vector_create.c
        ft_vector_delete.c
        ft_vector_delete_elem.c
        ft_vector_end.c
        ft_vector_iter.c
        ft_vector_iteri.c
        ft_vector_join.c
        ft_vector_join_fr.c
        ft_vector_push_back.c
        ft_vector_size.c
        ft_vector_tools.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
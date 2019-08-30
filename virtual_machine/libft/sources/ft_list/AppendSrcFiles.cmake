
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_list/"
        )

set( SourceFiles
        ft_lstadd_back.c
        ft_lstadd.c
        ft_lstcpy.c
        ft_lstcpy_elem.c
        ft_lstdel.c
        ft_lstdelone.c
        ft_lstforeach.c
        ft_lstiter.c
        ft_lstlen.c
        ft_lstmap.c
        ft_lstnew.c
        ft_lstrcpy.c
        ft_lstrev.c
        ft_lstsort.c
        ft_lstswap.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
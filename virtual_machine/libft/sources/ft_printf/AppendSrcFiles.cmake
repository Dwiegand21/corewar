
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_printf/"
        )

set( SourceFiles
        args.c
        char_tools.c
        free_printf.c
        ft_scale.c
        ldbl_1.c
        ldbl_4.c
        main_func.c
        postprocessing_2.c
        processing.c
        uni_encode.c
        checkers_1.c
        ft_printf.c
        ft_vprintf.c
        init2.c
        ldbl_2.c
        lft_1.c
        plist.c
        preprocessing.c
        validation.c
        char.c
        checkers_2.c
        init.c
        ldbl_3.c
        lft_2.c
        postprocessing_1.c
        print_result.c
        tools.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
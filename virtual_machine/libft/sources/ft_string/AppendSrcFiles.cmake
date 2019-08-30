
set( FileNamePrefix
        "${CMAKE_CURRENT_SOURCE_DIR}/sources/ft_string/"
        )

set( SourceFiles
        ft_atoi.c
        ft_isalnum.c
        ft_isalpha.c
        ft_isascii.c
        ft_isdigit.c
        ft_isprint.c
        ft_itoa.c
        ft_strcat.c
        ft_strchr.c
        ft_strclr.c
        ft_strcmp.c
        ft_strcpy.c
        ft_strdel.c
        ft_strdup.c
        ft_strequ.c
        ft_striter.c
        ft_striteri.c
        ft_strjoin.c
        ft_strlcat.c
        ft_strlen.c
        ft_strmap.c
        ft_strmapi.c
        ft_strncat.c
        ft_strncmp.c
        ft_strncpy.c
        ft_strnequ.c
        ft_strnequ_rev.c
        ft_strnew.c
        ft_strnstr.c
        ft_strrchr.c
        ft_strsplit.c
        ft_strstr.c
        ft_strsub.c
        ft_strtrim.c
        ft_tolower.c
        ft_toupper.c
        )

list( TRANSFORM SourceFiles PREPEND "${FileNamePrefix}" )

if( _LIB_SRC_DEF )
    list( APPEND LIB_SRC ${SourceFiles} )
endif()

unset( FileNamePrefix )
unset( SourceFiles )
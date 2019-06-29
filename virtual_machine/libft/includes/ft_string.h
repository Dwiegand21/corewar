//
// Created by axtazy on 6/9/19.
//

#ifndef LIBFT_FT_STRING_H
#define LIBFT_FT_STRING_H

#include <stdlib.h>

int				ft_atoi(const char *str);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

char			*ft_itoa(int n);

char			*ft_strcat(char *dst, const char *src);

char			*ft_strchr(const char *str, int c);

void			ft_strclr(char *s);

int				ft_strcmp(const char *s1, const char *s2);

char			*ft_strcpy(char *dst, const char *src);

void			ft_strdel(char **as);

char			*ft_strdup(const char *src);

int				ft_strequ(char const *s1, char const *s2);

void			ft_striter(char *s, void (*f)(char *));

void			ft_striteri(char *s, void (*f)(unsigned int, char *));

char			*ft_strjoin(char const *s1, char const *s2);

size_t			ft_strlcat(char *dst, const char *src, size_t size);

size_t			ft_strlen(const char *str);

char			*ft_strmap(char const *s, char (*f)(char));

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char			*ft_strncat(char *dst, const char *src, size_t n);

int				ft_strncmp(const char *s1, const char *s2, size_t n);

char			*ft_strncpy(char *dst, const char *src, size_t length);

int				ft_strnequ(char const *s1, char const *s2, size_t n);

int 			ft_strnequ_rev(const char *s1, const char *s2, size_t n);

char			*ft_strnew(size_t size);

char			*ft_strnstr(const char *hay, const char *needle, size_t length);

char			*ft_strrchr(const char *str, int c);

char			**ft_strsplit(char const *s, char c);

char			*ft_strstr(const char *haystack, const char *needle);

char			*ft_strsub(char const *s, unsigned int start, size_t length);

char			*ft_strtrim(char const *s);

int				ft_tolower(int c);

int				ft_toupper(int c);

#endif //LIBFT_FT_STRING_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axtazy <axtazy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:43:06 by dwiegand          #+#    #+#             */
/*   Updated: 2019/03/30 10:27:26 by axtazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# if defined __linux__

#  include <stdint.h>

# endif

typedef struct	s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}				t_list;

# define BUFF_SIZE 1024
# define MAX_SIZE_FD 20

int				ft_atoi(const char *str);

void			ft_bzero(void *dst, size_t length);

int				ft_isalnum(int c);

int				ft_isalpha(int c);

int				ft_isascii(int c);

int				ft_isdigit(int c);

int				ft_isprint(int c);

char			*ft_itoa(int n);

void			ft_lstadd(t_list **alst, t_list *new);

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_list			*ft_lstnew(void const *content, size_t content_size);

void			*ft_memalloc(size_t size);

void			*ft_memccpy(void *dst, const void *src, int c, size_t length);

void			*ft_memchr(const void *s, int c, size_t n);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t length);

void			ft_memdel(void **ap);

void			*ft_memmove(void *dst, const void *src, size_t length);

void			*ft_memset(void *dst, int value, size_t length);

void			ft_memzerdel(void *content, size_t length);

void			ft_putchar_fd(char c, int fd);

void			ft_putchar(char c);

void			ft_putendl_fd(char const *s, int fd);

void			ft_putendl(char const *s);

void			ft_putnbr_fd(int n, int fd);

void			ft_putnbr(int n);

void			ft_putstr_fd(char const *s, int fd);

void			ft_putstr(char const *s);

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

char			*ft_strnew(size_t size);

char			*ft_strnstr(const char *hay, const char *needle, size_t length);

char			*ft_strrchr(const char *str, int c);

char			**ft_strsplit(char const *s, char c);

char			*ft_strstr(const char *haystack, const char *needle);

char			*ft_strsub(char const *s, unsigned int start, size_t length);

char			*ft_strtrim(char const *s);

int				ft_tolower(int c);

int				ft_toupper(int c);

t_list			*ft_lstrev(t_list **alst);

size_t			ft_lstlen(t_list *lst);

void			ft_lstforeach(t_list *lst, void (*f)(void *, size_t));

t_list			*ft_lstcpy_elem(t_list *list);

int				ft_lstadd_back(t_list **alst, t_list *new);

t_list			*ft_lstcpy(t_list *lst);

t_list			*ft_lstrcpy(t_list *lst);

t_list			*ft_lstsplit(const void *data, int c, size_t length);

void			ft_lstputmem(t_list *lst);

void			ft_putmem(void *data, size_t length);

int				get_next_line(const int fd, char **line);

int				ft_getlines(int fd, t_list **list);

void			ft_putlst(t_list *lst);

void			ft_tabdel(void ***tab);

void			ft_error(char *error, int size);

#endif

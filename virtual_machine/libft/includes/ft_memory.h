//
// Created by axtazy on 6/9/19.
//

#ifndef LIBFT_FT_MEMORY_H
#define LIBFT_FT_MEMORY_H

#include <stddef.h>

void			ft_bzero(void *dst, size_t length);

void			*ft_memalloc(size_t size);

void			*ft_memccpy(void *dst, const void *src, int c, size_t length);

void			*ft_memchr(const void *s, int c, size_t n);

void 			ft_memclear_n_del(void *ptr, size_t size);

int				ft_memcmp(const void *s1, const void *s2, size_t n);

void			*ft_memcpy(void *dst, const void *src, size_t length);

void			ft_memdel(void **ap);

void			*ft_memmove(void *dst, const void *src, size_t length);

void			*ft_memset(void *dst, int value, size_t length);

#endif //LIBFT_FT_MEMORY_H

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwiegand <dwiegand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:40:33 by dwiegand          #+#    #+#             */
/*   Updated: 2018/12/01 20:43:47 by dwiegand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static int			ft_go(const char **str, char c)
{
	while (**str && **str == c)
		(*str)++;
	return (**str != 0);
}

static unsigned int	ft_words_count(char const *s, char c)
{
	unsigned int	res;

	res = 0;
	while (ft_go(&s, c))
	{
		res += 1;
		while (*s && *s != (const char)c)
			s++;
	}
	return (res);
}

static unsigned int	ft_word_len(const char *str, char c)
{
	const char		*head;

	head = str;
	while (*str && *str != c)
		str++;
	return (str - head);
}

static char			*ft_set(char **str, unsigned int length)
{
	char	*array;
	char	*head;

	head = NULL;
	array = NULL;
	if ((array = (char *)malloc(sizeof(char) * (length + 1))))
	{
		head = array;
		while (length--)
		{
			*array = **str;
			array++;
			(*str)++;
		}
		*array = 0;
	}
	return (head);
}

char				**ft_strsplit(char const *s, char c)
{
	size_t		i;
	char		**tab;

	tab = NULL;
	i = 0;
	if (s && (tab = malloc(sizeof(char *) * (ft_words_count(s, c) + 1))))
	{
		while (ft_go(&s, c))
		{
			if (!(tab[i++] = ft_set((char **)&s, ft_word_len(s, c))))
			{
				while (i-- > 0)
				{
					free(tab[i]);
					tab[i] = NULL;
				}
				free(tab);
				return (tab = NULL);
			}
		}
		tab[i] = NULL;
	}
	return (tab);
}

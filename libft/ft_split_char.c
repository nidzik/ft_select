/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <nidzik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:08:41 by nidzik            #+#    #+#             */
/*   Updated: 2017/05/26 14:08:48 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t			ft_cnt_word(char const *s, char c)
{
	int w;
	int i;

	i = 0;
	w = 0;
	while (*s != '\0')
	{
		if (i == 1 && (*s == c || *s == '\t'))
			i = 0;
		if (i == 0 && *s != c && *s != '\t')
		{
			i = 1;
			w++;
		}
		s++;
	}
	return (w);
}

static size_t			ft_size_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c && s[i] != '\t')
		i++;
	return (i);
}

static char const		*ft_ptr_move(char const *s, char c)
{
	while (*s == c || *s == '\t')
		s++;
	return (s);
}

char					**ft_split_char(char const *s, char c)
{
	char	**split;
	size_t	cnt_w;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	cnt_w = ft_cnt_word(s, c);
	if (!(split = (char **)malloc(sizeof(*split) * (cnt_w + 1))))
		return (NULL);
	while (cnt_w-- > 0)
	{
		s = ft_ptr_move(s, c);
		split[i] = (char *)malloc(sizeof(char) * (ft_size_word(s, c) + 1));
		if (split == NULL)
			return (NULL);
		l = 0;
		while (*s != '\0' && *s != c && *s != '\t')
			split[i][l++] = *s++;
		split[i++][l] = '\0';
		s = ft_ptr_move(s, c);
	}
	split[i] = NULL;
	return (split);
}

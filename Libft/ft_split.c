/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 18:36:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(const char *str, char c, size_t *arr_idx)
{
	size_t	ret;

	*arr_idx = 0;
	if (!c)
		return (1);
	ret = 0;
	while (*str)
	{
		if (*str != c && *str)
		{
			ret++;
			while (*str != c && *str)
				str++;
		}
		while (*str == c)
			str++;
	}
	return (ret);
}

char	**free_and_return(char **ret, size_t arr_idx)
{
	while (--arr_idx >= 0)
		free(ret[arr_idx]);
	free(ret);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	count;
	size_t	arr_idx;
	size_t	i;

	if (!s)
		return (NULL);
	count = count_word(s, c, &arr_idx);
	ret = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (arr_idx < count && *s)
	{
		i = 0;
		while (*s == c)
			s++;
		while (s[i] != c && s[i])
			i++;
		ret[arr_idx] = (char *)ft_calloc(i + 1, sizeof(char));
		if (!ret[arr_idx])
			return (free_and_return(ret, arr_idx));
		ft_strlcpy(ret[arr_idx++], s, i + 1);
		s += i;
	}
	return (ret);
}

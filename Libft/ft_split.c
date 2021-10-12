/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:32 by mishin           ###   ########.fr       */
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

static void		free_all(char **ret, size_t arr_idx)
{
	while (--arr_idx >= 0)
		free(ret[arr_idx]);
	free(ret);
}

char			**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	count;
	size_t	arr_idx;
	size_t	i;

	if (!s)
		return (NULL);
	count = count_word(s, c, &arr_idx);
	if (!(ret = (char **)ft_calloc(count + 1, sizeof(char *))))
		return (NULL);
	while (!(i = 0) && arr_idx < count && *s)
	{
		while (*s == c)
			s++;
		while (s[i] != c && s[i])
			i++;
		if (!(ret[arr_idx] = (char *)ft_calloc(i + 1, sizeof(char))))
		{
			free_all(ret, arr_idx);
			return (NULL);
		}
		ft_strlcpy(ret[arr_idx++], s, i + 1);
		s += i;
	}
	return (ret);
}

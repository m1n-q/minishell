/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 15:13:55 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static size_t	trimlen(const char *str, const char *set)
{
	size_t	to_be_trimmed;
	size_t	len;

	to_be_trimmed = 0;
	len = ft_strlen(str);
	str--;
	while (isinset(*++str, set) && *str)
		to_be_trimmed++;
	if (!*str)
		return (len - to_be_trimmed);
	while (*str)
		str++;
	while (isinset(*--str, set))
		to_be_trimmed++;
	return (len - to_be_trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	len = trimlen(s1, set);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = 0;
	while (isinset(*s1, set) && *s1)
		s1++;
	if (!*s1)
		return (ret);
	i = 0;
	while (i < len)
		ret[i++] = *s1++;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		found;
	size_t	i;
	size_t	j;

	if (*needle == 0)
		return ((char *)haystack);
	found = 0;
	i = -1;
	while (haystack[++i] && i < len)
	{
		if (haystack[i] == *needle)
		{
			found = 1;
			j = -1;
			while (needle[++j] && haystack[i + j] && i + j < len && found)
				if (haystack[i + j] != needle[j])
					found = 0;
		}
		if (found && !needle[j])
			return ((char *)(haystack + i));
	}
	return (NULL);
}

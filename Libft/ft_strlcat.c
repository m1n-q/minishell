/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;

	i = 0;
	j = 0;
	while (dst[i] && i < dstsize)
		i++;
	len_dst = i;
	while (src[j])
	{
		if (i + 1 < dstsize)
			dst[i++] = src[j++];
		else
			j++;
	}
	if (i < dstsize)
		dst[i] = 0;
	return (len_dst + j);
}

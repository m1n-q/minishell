/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;

	if (!src)
		return (0);
	if (!dst)
		return (ft_strlen(src));
	idx = 0;
	while (src[idx] && idx + 1 < dstsize)
	{
		dst[idx] = src[idx];
		idx++;
	}
	if (dstsize)
		dst[idx] = 0;
	while (src[idx])
		idx++;
	return (idx);
}

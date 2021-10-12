/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*src_tmp;
	unsigned char		*dst_tmp;
	size_t				i;

	src_tmp = src;
	dst_tmp = dst;
	if (!dst && !src)
		return (dst);
	i = 0;
	while (i < n)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (dst);
}

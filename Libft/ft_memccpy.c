/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*src_tmp;
	unsigned char		*dst_tmp;
	unsigned char		val;
	size_t				i;

	val = c;
	src_tmp = src;
	dst_tmp = dst;
	i = -1;
	while (++i < n)
	{
		dst_tmp[i] = src_tmp[i];
		if (src_tmp[i] == val)
			return ((void *)(dst_tmp + ++i));
	}
	return (NULL);
}

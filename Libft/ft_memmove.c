/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*src_tmp;
	unsigned char		*dst_tmp;
	size_t				i;

	if (!dst && !src)
		return (dst);
	src_tmp = src;
	dst_tmp = dst;
	i = -1;
	if (src_tmp < dst_tmp)
		while (len-- > 0)
			dst_tmp[len] = src_tmp[len];
	else if (dst_tmp < src_tmp)
		while (++i < len)
			dst_tmp[i] = src_tmp[i];
	return (dst);
}

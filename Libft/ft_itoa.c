/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_check(long long llnb)
{
	size_t			len;

	if (!llnb)
		return (1);
	len = 0;
	if (llnb < 0)
	{
		llnb *= -1;
		len++;
	}
	while (llnb)
	{
		llnb /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int nbr)
{
	long long	llnb;
	size_t		len;
	char		*ret;
	int			sign;

	sign = 1;
	llnb = nbr;
	len = len_check(llnb);
	if (nbr < 0)
	{
		llnb *= -1;
		sign *= -1;
	}
	if (!(ret = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	if (!llnb)
		ret[0] = '0';
	while (llnb)
	{
		ret[--len] = llnb % 10 + '0';
		llnb /= 10;
	}
	if (sign == -1)
		ret[0] = '-';
	return (ret);
}

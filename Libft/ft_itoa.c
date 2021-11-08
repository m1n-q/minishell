/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 15:28:01 by kyumlee          ###   ########.fr       */
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

void	set_neg(int nbr, long long *llnb, int *sign)
{
	if (nbr < 0)
	{
		*llnb *= -1;
		*sign *= -1;
	}
}

char	*ft_itoa(int nbr)
{
	long long	llnb;
	size_t		len;
	char		*ret;
	int			sign;

	sign = 1;
	llnb = nbr;
	len = len_check(llnb);
	set_neg(nbr, &llnb, &sign);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
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

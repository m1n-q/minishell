/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:24:47 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 19:04:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long long	ret;
	int					sign;

	ret = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			ret *= 10;
			ret += *str - '0';
		}
		else
			break ;
		str++;
	}
	if (ret > 9223372036854775807ULL)
		return (sign == 1 ? -1 : 0);
	return ((int)(sign * ret));
}

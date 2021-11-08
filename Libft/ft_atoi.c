/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:24:47 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 18:07:43 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	unsigned long long	ret;
	int					sign;

	ret = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (ft_isdigit(*str))
	{
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	if (ret > 9223372036854775807ULL && sign == 1)
		return (-1);
	else if (ret > 9223372036854775807ULL && sign != 1)
		return (0);
	return ((int)(sign * ret));
}

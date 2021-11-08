/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:24:47 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 15:24:20 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
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
	while (ft_isspace(*str))
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:49:25 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 18:40:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	putchar(int c)
{
	if (write(STDOUT_FILENO, &c, 1) == -1)
		return (-1);
	return (c);
}

long long atonum(const char *str, int *len)
{
	long long ret;
	int sign;

	ret = 0;
	sign = 1;
	if ((*str == '-' || *str == '+') && ++(*len))
		if (*str++ == '-')
			sign *= -1;
	if (!('0' <= *str && *str <= '9'))
		return (NON_NUMERIC);
	while (*str)
	{
		(*len)++;
		if ('0' <= *str && *str <= '9')
			ret = (ret * 10) + (*str - '0');
		else
		{
			(*len)--;
			break;
		}
		str++;
	}
	return ((sign * ret));
}

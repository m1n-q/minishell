/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:49:25 by mishin            #+#    #+#             */
/*   Updated: 2021/10/28 19:25:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	putchar(int c)
{
	if (write(STDOUT_FILENO, &c, 1) == -1)
		return (-1);
	return (c);
}

int atonum(const char *str, int *len, long long *retval)
{
	long long ret;
	int sign;

	ret = 0;
	sign = 1;
	if (!str)
		return (-1);
	if ((*str == '-' || *str == '+') && ++(*len))
		if (*str++ == '-')
			sign *= -1;
	if (!('0' <= *str && *str <= '9'))
		return (-1);
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
	*retval = (sign * ret);
	return (0);
}

int	get_argc(char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

void	free_till(int index, char **arr)
{
	int	i;

	i = -1;
	while (++i < index)
		free(arr[i]);
}

int	is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && \
		!ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

int	skip_space(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (1);
	return (0);
}

intmax_t	ft_strtoimax(const char *nptr, char **endptr)	//FIXME
{
	const char *s;
	char c;
	uintmax_t acc;
	uintmax_t cutoff;
	int	cutlim;
	int neg;
	int any;

	s = nptr;
	do {
		c = *s++;
	} while (ft_isspace(c));
	if (c == '-') {
		neg = 1;
		c = *s++;
	} else {
		neg = 0;
		if (c == '+')
			c = *s++;
	}
	acc = 0;
	any = 0;


	cutoff = neg ? (uintmax_t)-(INTMAX_MIN + INTMAX_MAX) + INTMAX_MAX
	    : INTMAX_MAX;
	cutlim = cutoff % 10;
	cutoff /= 10;
	for ( ; ; c = *s++) {
		if (c >= '0' && c <= '9')
			c -= '0';
		else
			break;
		if (c >= 10)
			break;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= 10;
			acc += c;
		}
	}
	if (any < 0) {
		acc = neg ? INTMAX_MIN : INTMAX_MAX;
		errno = ERANGE;
	} else if (!any) {
		errno = EINVAL;
	} else if (neg)
		acc = -acc;
	if (endptr != NULL)
		*endptr = (char *)(any ? s - 1 : nptr);
	return (acc);
}

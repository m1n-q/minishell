/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:49:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 17:22:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinjoin(char *a, char *b, char *c)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(a, b);
	ret = ft_strjoin(tmp, c);
	free(tmp);
	return (ret);

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

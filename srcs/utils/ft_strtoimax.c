/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoimax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:58:53 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 19:52:43 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_ws(const char **sp, t_result *r)
{
	r->neg = 0;
	while (ft_isspace(**sp))
		(*sp)++;
	if (**sp == '-' || **sp == '+')
	{
		if (**sp == '-')
			r->neg = 1;
		(*sp)++;
	}
}

static void	init(const char **sp, t_result *r, t_cut *cut, const char *nptr)
{
	*sp = nptr;
	skip_ws(sp, r);
	r->any = 0;
	r->acc = 0;
	if (r->neg)
		cut->off = INTMAX_MIN;
	else
		cut->off = INTMAX_MAX;
	cut->lim = cut->off % 10;
	cut->off /= 10;
}

static intmax_t	check_result(t_result r, const char *s, \
						const char *nptr, char **endptr)
{
	if (r.any < 0)
	{
		if (r.neg)
			r.acc = INTMAX_MIN;
		else
			r.acc = INTMAX_MAX;
		errno = ERANGE;
	}
	else if (!r.any)
		errno = EINVAL;
	else if (r.neg)
		r.acc = -r.acc;
	if (endptr != NULL)
	{
		if (r.any)
			*endptr = (char *)s;
		else
			*endptr = (char *)nptr;
	}
	return (r.acc);
}

intmax_t	ft_strtoimax(const char *nptr, char **endptr)
{
	const char	*s;
	char		c;
	t_result	r;
	t_cut		cut;

	init(&s, &r, &cut, nptr);
	c = *s;
	while (1)
	{
		if (c >= '0' && c <= '9')
			c -= '0';
		else
			break ;
		if (c >= 10)
			break ;
		if (r.any < 0 || r.acc > cut.off || (r.acc == cut.off && c > cut.lim))
			r.any = -1;
		else
		{
			r.any = 1;
			r.acc = (r.acc * 10) + c;
		}
		c = *++s;
	}
	return (check_result(r, s, nptr, endptr));
}

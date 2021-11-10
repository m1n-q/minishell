/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 13:49:42 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* count length of a string that is enclosed by q marks */
int	case_q(char *s)
{
	int		ret;
	char	c;

	ret = 2;
	if (is_q(*s))
	{
		c = *s++;
		while (*s && *s++ != c)
			ret++;
		while (*s && !ft_isspace(*s++))
			ret++;
	}
	return (ret);
}

/* count length of a string that is not enclosed by q marks */
int	case_default(char *s)
{
	int		ret;
	char	c;

	c = 0;
	ret = 0;
	while (*s && !ft_isspace(*s))
	{
		ret++;
		if (is_q(*s))
		{
			c = *s++;
			while (*s && *s != c && ret++)
				s++;
			ret++;
			s++;
		}
		else
			s++;
	}
	return (ret);
}

/* count length of a string */
int	cnt_str_len(char *s)
{
	if (is_q(*s))
		return (case_q(s));
	else
		return (case_default(s));
}

/* memory allocation of a string */
char	*malloc_str(char **argv, int i, int len)
{
	argv[i] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!argv[i])
	{
		free_strs(argv, i);
		return (0);
	}
	return (argv[i]);
}

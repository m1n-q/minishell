/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:23 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/20 22:13:00 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* count length of an arg that is enclosed by quotes */
int	case_q(char *s)
{
	int	ret;

	ret = skip_q(s);
	while (s[ret] && !ft_isspace(s[ret]))
		ret++;
	return (ret);
}

/* count length of an arg that is not enclosed by quotes */
int	case_default(char *s)
{
	int		ret;
	char	c;

	ret = 0;
	c = 0;
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

/* count length of an arg */
int	cnt_str_len(char *s)
{
	if (is_q(*s))
		return (case_q(s));
	else
		return (case_default(s));
}

/* memory allocation of an arg */
char	*malloc_str(char **argv, int i, int len)
{
	argv[i] = (char *)calloc_(len + 1, sizeof(char));
	if (!argv[i])
	{
		free_till(i, argv);
		free(argv);
		return (0);
	}
	return (argv[i]);
}

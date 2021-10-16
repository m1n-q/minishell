/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:04:21 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/16 15:25:54 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* count length of a string that is enclosed by q marks */
int	case_q(char *s)
{
	int		ret;
	char	c;

	ret = 0;
	c = *s++;
	while (*s++ != c)
		ret++;
	ret += 2;
	while (*s && !ft_isspace(*s++))
		ret++;
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

/* malloc a string */
char	*malloc_str(char *s, char **ret, int i, int len)
{
	if (is_q(*s))
		len -= 2;
	ret[i] = malloc(sizeof(char) * (len + 1));
	if (!ret[i])
	{
		free_strs(ret, i);
		return (0);
	}
	return (ret[i]);
}

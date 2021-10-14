/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:04:21 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/15 00:20:57 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	case_q(char *s)
{
	int		ret;
	char	c;

	ret = 0;
	c = *s;
	s++;
	while (*s != c)
	{
		ret++;
		s++;
	}
	ret += 2;
	return (ret);
}

int	case_default(char *s)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (ft_isspace(*s))
			break ;
		ret++;
		s++;
	}
	return (ret);
}

/* count length of a word */
int	cnt_str_len(char *s)
{
	int	ret;

	ret = 0;
	if (*s == '"' || *s == '\'')
		return (case_q(s));
	else
		return (case_default(s));
}

char	*malloc_str(char *s, char **ret, int i, int len)
{
	if (*s == '"' || *s == '\'')
		len -= 2;
	ret[i] = malloc(sizeof(char) * (len + 1));
	if (!ret[i])
	{
		free_strs(ret, i);
		return (0);
	}
	return (ret[i]);
}

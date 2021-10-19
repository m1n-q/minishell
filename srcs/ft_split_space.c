/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:05:55 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/19 01:22:49 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	cnt_empty_q(char *s)
{
	int		ret;

	ret = 0;
	while (*s)
	{
		if (is_empty_q(s))
		{
			ret++;
			s += 2;
		}
		else
			s++;
	}
	return (ret);
}

/* remove all empty q's in the beginning */
char	*rm_empty_q(char *s)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(s) - cnt_empty_q(s) * 2;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (is_empty_q(s))
			s += 2;
		else
			ret[i++] = *s++;
		if (!*s)
			break ;
	}
	ret[i] = 0;
	return (ret);
}

char	**ft_split_space(char *s)
{
	int		i;
	int		str_len;
	char	**ret;

	if (!quotes_match(s))
		return (0);
	s = rm_empty_q(s);
	ret = malloc_strs(s);
	i = 0;
	str_len = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			str_len = cnt_str_len(s);
			ret[i] = malloc_str(s, ret, i, str_len);
			ret[i] = cpy_str(s, ret[i]);
			s += str_len;
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

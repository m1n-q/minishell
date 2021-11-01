/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:00:51 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/01 16:00:54 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if the numbers of each of the quotes are odd (mismatch) return 0,
 * otherwise return 1 */
int	quotes_match(char *s)
{
	char	c;
	int		cnt_q;

	cnt_q = 0;
	while (*s)
	{
		if (is_q(*s))
		{
			c = *s++;
			cnt_q++;
			while (*s)
			{
				if (*s == c)
				{
					cnt_q--;
					break ;
				}
				s++;
			}
		}
		s++;
	}
	return (1);
}

/* count empty sets of quotes */
int	cnt_empty_q(char *s)
{
	int		ret;

	ret = 0;
	while (*s)
	{
		if (is_empty_q(s) && *(s + 2) && !ft_isspace(*(s + 2)))
		{
			ret++;
			s += 2;
		}
		else
			s++;
	}
	return (ret);
}

/* remove all empty sets of quotes */
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
		if (is_empty_q(s) && *(s + 2) && !ft_isspace(*(s + 2)))
			s += 2;
		else
			ret[i++] = *s++;
		if (!*s)
			break ;
	}
	ret[i] = 0;
	return (ret);
}

char	**parse(char *s)
{
	int		i;
	int		str_len;
	char	**ret;

	if (!quotes_match(s))
		return (0);
	s = rm_empty_q(s);
	s = split_pipe_redir(s);
	ret = malloc_strs(s);
	i = 0;
	str_len = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			str_len = cnt_str_len(s);
			ret[i] = cpy_str(s, ret, &i);
			s += str_len - 1;
		}
		s++;
	}
	ret[i] = 0;
	return (ret);
}

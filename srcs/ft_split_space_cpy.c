/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_cpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:03:07 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/15 17:45:50 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* for words that have q marks in between the letters, trim those q marks */
char	*trim_q(char *s)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(s) - 2 + 1));
	if (!ret)
		return (0);
	i = -1;
	j = 0;
	while (++i < (int)ft_strlen(s) - 2)
	{
		if (is_q(s[j]))
//		if (s[j] == '"' || s[j] == '\'')
			j++;
		ret[i] = s[j++];
	}
	ret[i] = 0;
	return (ret);
}

/* check if a word has q marks in between the letters */
int	has_q(char *s)
{
	while (*s)
	{
		if (is_q(*s))
//		if (*s == '"' || *s == '\'')
			return (1);
		s++;
	}
	return (0);
}

/* copy a word that is enclosed by q marks from s to ret */
char	*cpy_q_str(char *s, char *ret, int i, int j)
{
	if (s[i] == '"')
	{
		while (s[++i] != '"')
			ret[j++] = s[i];
	}
	else if (s[i] == '\'')
	{
		while (s[++i] != '\'')
			ret[j++] = s[i];
	}
	ret[j] = 0;
	return (ret);
}

/* copy a word from s to ret */
char	*cpy_str(char *s, char *ret)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (is_q(*s))
//	if (*s == '"' || *s == '\'')
		return (cpy_q_str(s, ret, i, j));
	else
	{
		while (s[i])
		{
			ret[j++] = s[i++];
			if (s[i] == ' ')
				break ;
		}
	}
	ret[j] = 0;
	if (has_q(ret))
		ret = trim_q(ret);
	return (ret);
}

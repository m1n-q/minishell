/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:14:10 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 13:59:48 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

char	*cpy_delimiter(char *s, char *arg)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	free(arg);
	while (s[i] && !ft_isspace(s[i]))
		i++;
	ret = (char *)ft_calloc(i + 1, sizeof(char));		//LEAK
	if (!ret)
		return (0);
	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		ret[j++] = s[i++];
	ret[j] = 0;
	return (ret);
}

int	cnt_delimiter_len(char *s)
{
	char	c;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] && is_q(s[i]))
		{
			if (s[i + 1] && !is_q(s[i + 1]))
				ret += 2;
			c = s[i];
			while (s[++i] != c)
				ret++;
		}
		else if (s[i] && !is_q(s[i]))
			ret++;
		i++;
	}
	return (ret);
}

char	*adjust_delimiter(char *s)
{
	char	*ret;
	int		i;
	int		j;
	char	c;

	ret = (char *)ft_calloc(cnt_delimiter_len(s) + 1, sizeof(char));
	if (!ret)
		return (0);
	i = 0;
	j = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))
		{
			c = s[i];
			while (s[++i] != c)
				ret[j++] = s[i];
		}
		else
			ret[j++] = s[i];
		i++;
	}
	return (ret);
}

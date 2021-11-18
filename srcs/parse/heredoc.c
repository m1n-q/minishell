/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:14:10 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/18 14:39:50 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* copy the heredoc delimiter */
char	*cpy_delimiter(char *s, char *arg)
{
	int		i;
	int		j;
	char	c;
	char	*ret;

	i = 0;
	j = 0;
	free(arg);
	while (s[i] && !ft_isspace(s[i]))
		i++;
	ret = (char *)calloc_(i + 1, sizeof(char));
	i = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))
		{
			c = s[i];
			ret[j++] = c;
			while (s[++i] != c)
				ret[j++] = s[i];
		}
		ret[j++] = s[i++];
	}
	ret[j] = 0;
	return (ret);
}

/* count length of a heredoc delimiter */
int	cnt_delimiter_len(char *s)
{
	int		i;
	int		ret;
	char	c;

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

/* remove all quotes in a heredoc delimiter */
char	*adjust_delimiter(char *s)
{
	char	*ret;
	int		i;
	int		j;
	char	c;

	ret = (char *)calloc_(cnt_delimiter_len(s) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (s[i])
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

/* check if a delimiter is begins or ends with a quote */
int	check_delimiter(char **delim)
{
	char	*ret;
	char	*s;

	s = *delim;
	if (!is_q(s[0]) && !is_q(s[ft_strlen(s) - 1]))
		return (1);
	ret = adjust_delimiter(s);
	free(*delim);
	*delim = ret;
	return (0);
}

/* getenv with length */
char	*getenv_(char *s, int *i, int check)
{
	char	*tmp;
	char	*ret;
	int		j;

	j = 0;
	while (s[j] && !is_q(s[j]) && !ft_isspace(s[j]))
		j++;
	tmp = calloc_n_lcpy(s, j + 1);
	ret = getenv(tmp);
	free(tmp);
	if (check)
		*i = ++j;
	return (ret);
}

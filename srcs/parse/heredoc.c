/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:14:10 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/03 13:04:59 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* count heredocs */
int	cnt_heredoc(char *s)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (!ft_strncmp(s, "<<", 2))
		{
			ret++;
			s += 2;
		}
		else
			s++;
	}
	return (ret);
}

/* add quotes in front of and at the end of heredoc delimiter */
void	add_q(int *i, int *j, char *ret, char *s)
{
	char	c;

	if (s[*j] == '\'')
		ret[(*i)++] = '"';
	else if (s[*j] == '"')
		ret[(*i)++] = '\'';
	c = s[(*j)++];
	ret[(*i)++] = c;
	while (s[*j] != c)
		ret[(*i)++] = s[(*j)++];
	ret[(*i)++] = s[(*j)++];
	if (s[*j - 1] == '\'')
		ret[(*i)++] = '"';
	else if (s[*j - 1] == '"')
		ret[(*i)++] = '\'';
}

/* new string with heredoc delimiters surrounded by quotes */
char	*add_q_to_heredoc_del(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	i = 0;
	j = 0;
	len = ft_strlen(s) + (cnt_heredoc(s) * 2);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (s[j])
	{
		if (j >= 3 && is_q(s[j]) && s[j - 1] == ' '
			&& s[j - 2] == '<' && s[j - 3] == '<')
			add_q(&i, &j, ret, s);
		else
			ret[i++] = s[j++];
	}
	ret[i] = 0;
	return (ret);
}

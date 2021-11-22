/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:59 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 22:29:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	is_empty_q(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[i++];
	if (c == '$')
		return (0);
	if (s[i] && s[i + 1] && is_q(s[i]) && s[i] == s[i + 1])
	{
		if ((s[i + 2] && !ft_isspace(s[i + 2])) || !s[i + 2])
			return (1);
	}
	return (0);
}

/* if an arg is a delimiter of heredoc, maintain all empty quotes */
int	skip_empty_q_in_delimiter(char *s)
{
	int	i;

	i = 2;
	while (ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))
			i += skip_q(&s[i]) - 1;
		i++;
	}
	return (i);
}

/* count empty quotes */
int	cnt_empty_q(char *s)
{
	char	c;
	int		i;
	int		ret;

	c = 0;
	i = -1;
	ret = 0;
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			i += skip_empty_q_in_delimiter(&s[i]) - 1;
		else if (is_q(s[i]))
		{
			if (i > 0 && is_empty_q(&s[i - 1]))
			{
				i++;
				ret++;
			}
			else
				i += skip_q(&s[i]) - 1;
		}
	}
	return (ret);
}

/* remove empty quotes that are not separated by spaces */
char	*rm_empty_q(char *s)
{
	int		i;
	int		j;
	char	c;
	char	*ret;

	if (!cnt_empty_q(s))
		return (s);
	ret = (char *)calloc_((ft_strlen(s) - cnt_empty_q(s) * 2) + 1, \
	sizeof(char *));
	i = -1;
	j = 0;
	c = 0;
	while (s[++i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			i += skip_empty_q_in_delimiter(s);
		if (i > 0 && is_empty_q(&s[i - 1]))
			i++;
		else
			ret[j++] = s[i];
	}
	ret[j] = 0;
	free(s);
	return (ret);
}

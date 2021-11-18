/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:59 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/18 14:09:21 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if an arg is a delimiter of heredoc, maintain all empty quotes */
int	skip_empty_q_in_delimiter(char *s)
{
	int	i;

	i = 2;
	while (ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

/* count empty quotes */
int	cnt_empty_q(char *s)
{
	int		i;
	int		len;
	int		ret;
	char	c;

	i = 0;
	len = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
			i += skip_empty_q_in_delimiter(&s[i]) - 1;
		else if (is_q(s[i]))
		{
			c = s[i];
			while (s[++i] != c)
				len++;
			if (!len)
				ret++;
		}
		i++;
	}
	return (ret);
}

/* remove empty quotes that are not separated by spaces */
char	*rm_empty_q(char *s)
{
	int		i;
	int		len;
	char	*tofree;
	char	*ret;

	if (!cnt_empty_q(s))
		return (s);
	i = 0;
	len = ft_strlen(s) - cnt_empty_q(s) * 2;
	ret = (char *)calloc_(len + 1, sizeof(char));
	tofree = s;
	while (*s)
	{
		if (*s == '<' && *(s + 1) == '<')
			s += skip_empty_q_in_delimiter(s);
		if (is_empty_q(s) && ((*(s + 2) && !ft_isspace(*(s + 2))) || !*(s + 2)))
			s += 2;
		else
			ret[i++] = *s++;
	}
	ret[i] = 0;
	free(tofree);
	return (ret);
}

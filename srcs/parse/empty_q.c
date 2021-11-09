/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:59 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/09 18:08:15 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

char	*skip_empty_q_in_delimiter(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (&s[i]);
}

/* count empty sets of quotes */
int	cnt_empty_q(char *s)
{
	int		ret;
	int		len;
	char	c;

	ret = 0;
	len = 0;
	while (*s)
	{
		if (*s == '<' && *(s + 1) == '<')
			s = skip_empty_q_in_delimiter(s + 2);
		if (is_q(*s))
		{
			c = *s++;
			while (*s != c)
				s++;
			s++;
			if (*s && !ft_isspace(*s))
				ret++;
		}
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
	char	*tofree;

	if (!cnt_empty_q(s))
		return (s);
	tofree = s;
	i = 0;
	len = ft_strlen(s) - cnt_empty_q(s) * 2;
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s == '<' && *(s + 1) == '<')
			s = skip_empty_q_in_delimiter(s + 2);
		if (is_empty_q(s) && ((*(s + 2) && !ft_isspace(*(s + 2))) || !*(s + 2)))
			s += 2;
		else
			ret[i++] = *s++;
	}
	ret[i] = 0;
	free(tofree);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:05:55 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/16 23:01:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* parsing pipe and redirections */
char	*pipe_redir(char *s)
{
	if (ft_strlen(s) == 1)
	{
		if (*s == '|')
			s = (char *)PIPE;
		else if (*s == '<')
			s = (char *)REDIRECT_IN;
		else if (*s == '<')
			s = (char *)REDIRECT_OUT;
	}
	else if (ft_strlen(s) == 2)
	{
		if (*s == '<' && *(s + 1) == '<')
			s = (char *)HEREDOC;
		if (*s == '>' && *(s + 1) == '>')
			s = (char *)REDIRECT_APPEND;
	}
	return (s);
}

char	**ft_split_space(char *s)
{
	int		i;
	int		str_len;
	char	**ret;

	if (!check_quotes(s))
		return (0);
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
			ret[i] = pipe_redir(ret[i]);
			s += str_len;
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

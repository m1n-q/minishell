/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_cpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:03:07 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/19 01:24:41 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* typecast pipes and redirections */
char	*case_pipe_redir(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 1 && *s == '|')
		return ((char *)PIPE);
	if (len == 1 && *s == '<')
		return ((char *)REDIRECT_IN);
	if (len == 1 && *s == '>')
		return ((char *)REDIRECT_OUT);
	if (len == 2 && !ft_strncmp(s, "<<", len))
		return ((char *)HEREDOC);
	if (len == 2 && !ft_strncmp(s, ">>", len))
		return ((char *)REDIRECT_APPEND);
	return (s);
}

/* copy a string that is enclosed by q marks from (s) to (ret) */
char	*cpy_with_q(char *s, char *ret)
{
	char	c;
	int		i;

	i = 0;
	while (*s && !ft_isspace(*s))
	{
		c = *s++;
		while (*s && *s != c)
			ret[i++] = *s++;
		if (*++s && !ft_isspace(*s))
		{
			while (*s && !ft_isspace(*s) && !is_q(*s))
				ret[i++] = *s++;
		}
	}
	ret[i] = 0;
	return (ret);
}

/* copy a string that is not enclosed by q marks from (s) to (ret) */
char	*cpy_wo_q(char *s, char *ret)
{
	char	c;
	int		i;

	i = 0;
	ret[i++] = *s++;
	while (*s && !ft_isspace(*s))
	{
		if (is_q(*s))
		{
			c = *s++;
			while (*s && *s != c)
				ret[i++] = *s++;
		}
		else
			ret[i++] = *s++;
	}
	ret[i] = 0;
	ret = case_pipe_redir(ret);
	return (ret);
}

/* copy a string from (s) to (ret) */
char	*cpy_str(char *s, char *ret)
{
	if (is_q(*s))
		return (cpy_with_q(s, ret));
	else
		return (cpy_wo_q(s, ret));
}

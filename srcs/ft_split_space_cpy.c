/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_cpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:03:07 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/26 12:06:00 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	has_dollar_sign(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

/* typecast pipes and redirections */
char	*case_pipe_redir(char *s)
{
	if (is_equal(s, "|"))
		return ((char *)PIPE);
	if (is_equal(s, "<"))
		return ((char *)REDIRECT_IN);
	if (is_equal(s, ">"))
		return ((char *)REDIRECT_OUT);
	if (is_equal(s, "<<"))
		return ((char *)HEREDOC);
	if (is_equal(s, ">>"))
		return ((char *)REDIRECT_APPEND);
	return (s);
}

/* copy a string that is enclosed by q marks from (s) to (ret) */
char	*cpy_with_q(char *s, char *ret)
{
	char	c;
	int		i;

	i = 0;
	if (is_empty_q(s))
	{
		ret[0] = 0;
		return (ret);
	}
	while (*s && !ft_isspace(*s))
	{
		c = *s++;
		if (has_dollar_sign(s) && c == '"')
			return (case_env(s));
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
	if (has_dollar_sign(s))
		return (case_env(s));
	ret[i++] = *s++;
	while (*s && !ft_isspace(*s))
	{
		if (is_q(*s))
		{
			c = *s++;
			while (*s && *s != c)
				ret[i++] = *s++;
			s++;
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

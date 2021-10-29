/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_cpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:03:07 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/29 18:00:50 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	has_dollar_sign(char *s)
{
	if (*s == '"')
	{
		while (*++s != '"')
		{
			if (*s == '$')
				return (1);
		}
	}
	while (*s && !ft_isspace(*s))
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
		if (has_dollar_sign(s) && *s == '"')
			return (case_env(s));
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
char	*cpy_str(char *s, char **ret, int *i)
{
	int	len;

	len = cnt_str_len(s);
	ret[*i] = malloc_str(s, ret, *i, len);
	if (is_q(*s))
		ret[*i] = cpy_with_q(s, ret[*i]);
	else
		ret[*i] = cpy_wo_q(s, ret[*i]);
	(*i)++;
	return (ret[*i]);
}

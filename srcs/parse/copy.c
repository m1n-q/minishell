/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:02 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/09 18:15:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	has_dollar_sign(char *s)
{
	if (is_equal(s, "$")
		|| (*s == '"' && *(s + 1) == '$' && *(s + 2) == '"'))
		return (0);
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
	char	*ret;

	if (is_equal(s, "|"))
		ret = (char *)PIPE;
	else if (is_equal(s, "<"))
		ret = (char *)REDIRECT_IN;
	else if (is_equal(s, ">"))
		ret = (char *)REDIRECT_OUT;
	else if (is_equal(s, "<<"))
		ret = (char *)HEREDOC;
	else if (is_equal(s, ">>"))
		ret = (char *)REDIRECT_APPEND;
	else
		ret = s;
	if (ret != s)
		free(s);
	return (ret);
}

/* copy a string that is enclosed by q marks from (s) to (ret) */
char	*cpy_with_q(char *s, char *argv, char **argvs, int j)
{
	char	c;
	int		i;

	i = 0;
	if (argvs[j - 1] == (char *)HEREDOC)
		return (cpy_delimiter(s));
	while (*s && !ft_isspace(*s))
	{
		if (has_dollar_sign(s) && *s == '"')
			return (case_env(s + 1, '"'));
		c = *s++;
		while (*s && *s != c)
			argv[i++] = *s++;
		if (*++s && !ft_isspace(*s))
		{
			while (*s && !ft_isspace(*s) && !is_q(*s))
				argv[i++] = *s++;
		}
	}
	argv[i] = 0;
	return (argv);
}

/* copy a string that is not enclosed by q marks from (s) to (ret) */
char	*cpy_wo_q(char *s, char *argv)
{
	char	c;
	int		i;

	i = 0;
	if (has_dollar_sign(s))
		return (case_env(s, ' '));
	argv[i++] = *s++;
	while (*s && !ft_isspace(*s))
	{
		if (is_q(*s))
		{
			c = *s++;
			while (*s && *s != c)
				argv[i++] = *s++;
			s++;
		}
		else
			argv[i++] = *s++;
	}
	argv[i] = 0;
	argv = case_pipe_redir(argv);
	return (argv);
}

/* copy a string from (s) to (ret) */
char	*cpy_str(char *s, char **argv, int i)
{
	int		len;

	len = cnt_str_len(s);
	argv[i] = malloc_str(argv, i, len);
	if (is_q(*s))
		argv[i] = cpy_with_q(s, argv[i], argv, i);
	else
		argv[i] = cpy_wo_q(s, argv[i]);
	return (argv[i]);
}

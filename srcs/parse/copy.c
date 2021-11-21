/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:02 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/21 18:02:45 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* typecast pipes and redirections */
char	*case_pipe_redir(char *s)
{
	char	*ret;

	if (is_equal(s, "|"))
		ret = PIPE;
	else if (is_equal(s, "<"))
		ret = REDIRECT_IN;
	else if (is_equal(s, ">"))
		ret = REDIRECT_OUT;
	else if (is_equal(s, "<<"))
		ret = HEREDOC;
	else if (is_equal(s, ">>"))
		ret = REDIRECT_APPEND;
	else
		ret = s;
	if (ret != s)
		free(s);
	return (ret);
}

/* copy an arg that is enclosed by quotes */
char	*cpy_with_q(char *s, char *arg, char **argv, int j)
{
	int		i;
	char	c;

	i = 0;
	if (j > 0 && argv[j - 1] == HEREDOC)
		return (cpy_delimiter(s, arg));
	return (case_env(s, arg, argv, j));
	// while (*s && !ft_isspace(*s))
	// {
	// 	if (has_dollar_sign(s) && is_q(*s))
	// 		return (case_env(s, arg, argv, j));
	// 	c = *s++;
	// 	while (*s && *s != c)
	// 		arg[i++] = *s++;
	// 	if (*++s && !ft_isspace(*s))
	// 	{
	// 		while (*s && !ft_isspace(*s) && !is_q(*s))
	// 			arg[i++] = *s++;
	// 	}
	// }
	// arg[i] = 0;
	return (arg);
}

/* copy an arg that is not enclosed by quotes */
char	*cpy_wo_q(char *s, char *arg, char **argv, int j)
{
	int		i;
	char	c;

	i = 0;
	if (j > 0 && argv[j - 1] == HEREDOC && !is_pipe_redir(s[0]))
		return (cpy_delimiter(s, arg));
	if (has_dollar_sign(s) && (j == 0
			|| (j > 0 && argv[j - 1] != HEREDOC)))
		return (case_env(s, arg, argv, j));
	arg[i++] = *s++;
	while (*s && !ft_isspace(*s))
	{
		if (is_q(*s))
		{
			c = *s++;
			while (*s && *s != c)
				arg[i++] = *s++;
			s++;
		}
		else
			arg[i++] = *s++;
	}
	arg[i] = 0;
	arg = case_pipe_redir(arg);
	return (arg);
}

/* copy an arg */
char	**cpy_str(char *s, char **argv, int *i, int argc)
{
	int		len;

	len = cnt_str_len(s);
	argv[*i] = malloc_str(argv, *i, len);
	if (is_q(*s))
		argv[*i] = cpy_with_q(s, argv[*i], argv, *i);
	else
		argv[*i] = cpy_wo_q(s, argv[*i], argv, *i);
	if (argv[*i] == (char *)AMBIG_REDIR)
	{
		free_till(*i, argv);
		free(argv);
		return (AMBIG_REDIR);
	}
	if (argv[*i] && was_expanded(s))
	{
		if (has_quotes(s))
			return (just_join_with_arg(argv, i, argc, s));
		else
			return (split_and_join_till(argv, i, argc, s));
	}
	(*i)++;
	return (argv);
}

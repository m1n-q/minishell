/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:02 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/21 21:56:20 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* typecast pipes and redirections */
char	*typecast_pipe_redir(char *s)
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

char	*copy_env(char *arg, char *prev_arg)
{
	int		i;
	char	*ret;

	i = 0;
	ret = 0;
	while (arg[i])
	{
		if (arg[i] != '$')
			i += copy_non_env(&arg[i], &ret);
		else
			i += copy_env_val(&arg[i], &ret, prev_arg);
		if (ret == (char *)AMBIG_REDIR)
			return (ret);
	}
	free(arg);
	return (ret);
}

char	*adjust_arg(char **argv, char *arg, int i)
{
	char	*prev_arg;
	char	*ret;

	prev_arg = 0;
	if (i > 0)
		prev_arg = argv[i - 1];
	ret = 0;
	if (prev_arg == HEREDOC)
		return (arg);
	if (expand(arg) != -1)
		return (copy_env(arg, prev_arg));
	else
		return (arg);
	return (ret);
}

/* copy an arg */
char	**copy_arg(char *s, char **argv, int *i, int argc)
{
	int		len;

	len = cnt_str_len(s);
	argv[*i] = malloc_str(argv, *i, len);
	ft_strlcpy(argv[*i], s, len + 1);
	argv[*i] = adjust_arg(argv, argv[*i], *i);
	argv[*i] = typecast_pipe_redir(argv[*i]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:02 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 22:29:13 by mishin           ###   ########.fr       */
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
		if (arg[i] != '$' && !is_q(arg[i]))
			i += copy_non_env(&arg[i], &ret);
		else if (arg[i] == '$')
			i += copy_env_val(&arg[i], &ret, prev_arg, arg[i]);
		else if (is_q(arg[i]))
			i += copy_quotes(&arg[i], &ret, prev_arg, arg[i]);
		if (ret == (char *)AMBIG_REDIR)
			return (ambiguous_redirect_error(arg));
	}
	free(arg);
	return (ret);
}

char	*adjust_arg(char **argv, char *arg, int i, int *is_delimiter)
{
	char	*prev_arg;
	char	*ret;

	prev_arg = 0;
	ret = 0;
	if (i > 0)
		prev_arg = argv[i - 1];
	if (prev_arg == HEREDOC)
	{
		*is_delimiter = 1;
		return (arg);
	}
	if (expand(arg) != -1)
		ret = copy_env(arg, prev_arg);
	else
		ret = typecast_pipe_redir(arg);
	return (ret);
}

/* copy an arg */
char	**copy_arg(char *s, char **argv, int *i, int argc)
{
	int	len;
	int	is_delimiter;

	len = cnt_str_len(s);
	is_delimiter = 0;
	argv[*i] = malloc_str(argv, *i, len);
	ft_strlcpy(argv[*i], s, len + 1);
	argv[*i] = adjust_arg(argv, argv[*i], *i, &is_delimiter);
	if (argv[*i] == (char *)AMBIG_REDIR)
	{
		free_till(*i, argv);
		free(argv);
		return (AMBIG_REDIR);
	}
	if (argv[*i] && !is_delimiter)
		return (split_and_trim_quotes(argv, i, argc));
	(*i)++;
	return (argv);
}

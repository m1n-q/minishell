/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:35:14 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/04 20:52:33 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	is_pipe_err(char **argv, int i)
{
	if (argv[0] == (char *)PIPE)
		return (1);
	if (i == 1 && argv[i] == (char *)PIPE)
	{
		if (argv[0] == (char *)REDIRECT_OUT)
			return (2);
		else if (argv[0] < (char *)REDIRECT_OUT)
			return (1);
	}
	if (i > 1 && argv[0] != (char *)REDIRECT_OUT && argv[1] == (char *)PIPE)
		return (1);
	if (argv[i] == (char *)PIPE && argv[i - 1] <= (char *)REDIRECT_OUT)
		return (1);
	return (0);
}

int	is_double_pipe_err(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] > (char *)REDIRECT_APPEND)
			if (is_equal(argv[i], "||"))
				return (1);
		i++;
	}
	return (0);
}

char	**redir_err(char **argv, int i)
{
	if (i == 0)
		return (syntax_error((char **)REDIR_ERR, "`newline'", EX_USAGE));
	if (i > 0)
	{
		if ((argv[0] != (char *)PIPE && argv[1] == (char *)REDIRECT_IN)
			|| (argv[0] == (char *)REDIRECT_OUT && \
				argv[1] == (char *)PIPE && argv[2] == (char *)REDIRECT_IN))
			return (syntax_error((char **)REDIR_ERR, "`<'", EX_USAGE));
		else if ((argv[0] != (char *)PIPE && argv[1] == (char *)REDIRECT_OUT)
			|| (argv[0] == (char *)REDIRECT_OUT && \
				argv[1] == (char *)PIPE && argv[2] == (char *)REDIRECT_OUT))
			return (syntax_error((char **)REDIR_ERR, "`>'", EX_USAGE));
		else if ((argv[0] != (char *)PIPE && argv[1] == (char *)REDIRECT_APPEND)
			|| (argv[0] == (char *)REDIRECT_OUT && \
				argv[1] == (char *)PIPE && argv[2] == (char *)REDIRECT_APPEND))
			return (syntax_error((char **)REDIR_ERR, "`>>'", EX_USAGE));
		else if ((argv[0] != (char *)PIPE && argv[1] == (char *)HEREDOC)
			|| (argv[0] == (char *)REDIRECT_OUT && \
				argv[1] == (char *)PIPE && argv[2] == (char *)HEREDOC))
			return (syntax_error((char **)REDIR_ERR, "`<<'", EX_USAGE));
	}
	return (argv);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:35:14 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/13 17:50:06 by shin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	find_token_error(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		while (argv[i] && is_token(argv[i]) == 0)
			i++;
		if (argv[i] == NULL)
			return (-1);
		if (is_redir_token(argv[i]) && argv[i + 1] == NULL)
			return (i + 1);
		if (is_pipe_token(argv[i]))
		{

			if (is_token(argv[i + 1]) || \
				(i > 0 && is_token(argv[i - 1]) && argv[i + 1] == NULL) || \
				(i == 0 && argv[i + 1] == NULL))
			return (i);
		}
		i++;
	}
	return (-1);
}

char	**token_error(char **argv)
{
	int		i;
	char	*tok;
	char	**e;

	i = find_token_error(argv);
	e = 0;
	if (i == -1)
		return (0);
	tok = toktos(argv[i]);
	if (is_pipe_token(argv[i]))
		e = (char **)PIPE_ERR;
	else if (is_redir_token(argv[i]) || argv[i] == NULL)
		e = (char **)REDIR_ERR;
	if (e)
	{
		syntax_error((char **)REDIR_ERR, tok, EX_USAGE);
		free_till(get_argc(argv), argv);
		free(argv);
	}
	free(tok);
	return (e);
}

/*int	is_pipe_err(char **argv, int i)
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
	if (i > 1 && argv[0] != (char *)REDIRECT_OUT
		&& argv[0] <= (char *)REDIRECT_APPEND && argv[1] == (char *)PIPE)
		return (1);
	if (argv[i] == (char *)PIPE && argv[i - 1] <= (char *)REDIRECT_APPEND)
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

int	is_invalid_redir(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i] == (char *)REDIRECT_IN
			&& argv[i + 1] == (char *)REDIRECT_OUT)
			return (1);
		if (argv[i] == (char *)REDIRECT_OUT
			&& argv[i + 1] == (char *)REDIRECT_IN)
			return (2);
	}
	return (0);
}

int	is_redir_err(char **argv, int i)
{
	if (is_invalid_redir(argv) == 1)
		return (1);
	else if (is_invalid_redir(argv) == 2)
		return (2);
	else if (argv[i] >= (char *)4LL && argv[i] <= (char *)7LL)
		return (3);
	else if ((argv[0] != (char *)PIPE && argv[i] == (char *)REDIRECT_IN)
		|| (argv[0] == (char *)REDIRECT_OUT && \
			argv[1] == (char *)PIPE && argv[2] == (char *)REDIRECT_IN))
		return (4);
	else if ((argv[0] != (char *)PIPE && argv[i] == (char *)REDIRECT_OUT)
		|| (argv[0] == (char *)REDIRECT_OUT && \
			argv[1] == (char *)PIPE && argv[2] == (char *)REDIRECT_OUT))
		return (5);
	else if ((argv[0] != (char *)PIPE && argv[i] == (char *)REDIRECT_APPEND)
		|| (argv[0] == (char *)REDIRECT_OUT && \
			argv[1] == (char *)PIPE && argv[2] == (char *)REDIRECT_APPEND))
		return (6);
	else if ((argv[0] != (char *)PIPE && argv[i] == (char *)HEREDOC)
		|| (argv[0] == (char *)REDIRECT_OUT && \
			argv[1] == (char *)PIPE && argv[2] == (char *)HEREDOC))
		return (7);
	return (0);
}

char	**return_redir_err(int err_num, char **argv)
{
	if (err_num == 1)
		return (syntax_error((char **)INVALID_REDIR, "`<>'", EX_USAGE, argv));
	if (err_num == 2)
		return (syntax_error((char **)INVALID_REDIR, "`><'", EX_USAGE, argv));
	if (err_num == 3)
		return (syntax_error((char **)REDIR_ERR, "`newline'", EX_USAGE, argv));
	if (err_num == 4)
		return (syntax_error((char **)REDIR_ERR, "`<'", EX_USAGE, argv));
	if (err_num == 5)
		return (syntax_error((char **)REDIR_ERR, "`>'", EX_USAGE, argv));
	if (err_num == 6)
		return (syntax_error((char **)REDIR_ERR, "`>>'", EX_USAGE, argv));
	if (err_num == 7)
		return (syntax_error((char **)REDIR_ERR, "`<<'", EX_USAGE, argv));
	return (0);
}*/

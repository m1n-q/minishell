/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:35:14 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/18 14:00:31 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* find token error (token: pipe, redirections) */
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
		if (is_redir_token(argv[i])
			&& (argv[i + 1] == NULL || is_redir_token(argv[i + 1])))
			return (i + 1);
		if (is_pipe_token(argv[i]))
		{
			if (is_token(argv[i + 1]) || \
				(i > 0 && is_token(argv[i - 1])) || \
				i == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

/* return syntax error when token error */
char	**token_error(char **argv)
{
	int		i;
	char	**e;
	char	*tok;

	i = find_token_error(argv);
	e = 0;
	if (i == -1)
		return (0);
	tok = toktos(argv[i]);
	if (is_pipe_token(argv[i]))
		e = PIPE_ERR;
	else if (is_redir_token(argv[i]) || argv[i] == NULL)
		e = REDIR_ERR;
	if (e)
	{
		syntax_error(REDIR_ERR, tok, EX_USAGE);
		free_till(get_argc(argv), argv);
		free(argv);
	}
	free(tok);
	return (e);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:35:14 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/16 17:57:02 by mishin           ###   ########.fr       */
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
		if (is_redir_token(argv[i])
			&& (argv[i + 1] == NULL || is_redir_token(argv[i + 1])))
			return (i + 1);
		if (is_pipe_token(argv[i]))
		{
			if (is_token(argv[i + 1]) || \
				(i > 0 && is_token(argv[i - 1])) || \
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

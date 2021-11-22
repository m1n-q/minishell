/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:45:54 by mishin            #+#    #+#             */
/*   Updated: 2021/11/22 17:42:21 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

char	*toktos(char *tok)
{
	if (tok == NULL)
		return (joinjoin("`", "newline", "'"));
	if (tok == PIPE)
		return (joinjoin("`", "|", "'"));
	if (tok == HEREDOC)
		return (joinjoin("`", "<<", "'"));
	if (tok == REDIRECT_IN)
		return (joinjoin("`", "<", "'"));
	if (tok == REDIRECT_OUT)
		return (joinjoin("`", ">", "'"));
	if (tok == REDIRECT_APPEND)
		return (joinjoin("`", ">>", "'"));
	return (NULL);
}

int	is_redir_token(char *s)
{
	if (s && (s == HEREDOC || \
			s == REDIRECT_IN || \
			s == REDIRECT_OUT || \
			s == REDIRECT_APPEND))
		return (1);
	return (0);
}

int	is_pipe_token(char *s)
{
	if (s && s == PIPE)
		return (1);
	return (0);
}

int	is_token(char *s)
{
	if (s == NULL)
		return (0);
	if (is_redir_token(s) || is_pipe_token(s))
		return (1);
	return (0);
}

int	is_empty(char *s)
{
	if (!s)
		return (0);
	if (s == EMPTY_VAR)
		return (1);
	return (0);
}

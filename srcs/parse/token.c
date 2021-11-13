/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:45:54 by mishin            #+#    #+#             */
/*   Updated: 2021/11/13 17:02:42 by mishin           ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*toktos(char *tok)
{
	if (tok == NULL)
		return (joinjoin("`", "newline", "'"));
	if (tok == (char *)PIPE)
		return (joinjoin("`", "|", "'"));
	if (tok == (char *)HEREDOC)
		return (joinjoin("`", "<<", "'"));	
	if (tok == (char *)REDIRECT_IN)
		return (joinjoin("`", "<", "'"));	
	if (tok == (char *)REDIRECT_OUT)
		return (joinjoin("`", ">", "'"));	
	if (tok == (char *)REDIRECT_APPEND)
		return (joinjoin("`", ">>", "'"));
	return (NULL);
}

int	is_token(char *s)
{
	if (s == NULL)
		return (0);
	if (is_redir_token(s) || is_pipe_token(s))
		return (1);
	return (0);
}

int	is_redir_token(char *s)
{
	if (s && (s == (char *)HEREDOC || \
			s == (char *)REDIRECT_IN || \
			s == (char *)REDIRECT_OUT || \
			s == (char *)REDIRECT_APPEND))
		return (1);
	return (0);
}

int	is_pipe_token(char *s)
{
	if (s && s == (char *)PIPE)
		return (1);
	return (0);
}


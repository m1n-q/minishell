/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:40:16 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/03 21:47:18 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

void	redir_in(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		get_or_set_exitcode(SET, EXECUTION_FAILURE);
		builtin_error(NULL, file, strerror(errno), 0);
	}
	if (cmd->redir_stream.in != DEFAULT)
		close(cmd->redir_stream.in);
	cmd->redir_stream.in = fd;
}

void	redir_out(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		get_or_set_exitcode(SET, EXECUTION_FAILURE);
		builtin_error(NULL, file, strerror(errno), 0);
	}
	if (cmd->redir_stream.out != DEFAULT)
		close(cmd->redir_stream.out);
	cmd->redir_stream.out = fd;
}

void	redir_append(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		get_or_set_exitcode(SET, EXECUTION_FAILURE);
		builtin_error(NULL, file, strerror(errno), 0);
	}
	if (cmd->redir_stream.out != DEFAULT)
		close(cmd->redir_stream.out);
	cmd->redir_stream.out = fd;
}

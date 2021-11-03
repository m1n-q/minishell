/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:22:01 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 21:01:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->any_err = 0;
	cmd->pipe[0] = 0;
	cmd->pipe[1] = 1;
	cmd->pipe_stream.in = DEFAULT;
	cmd->pipe_stream.out = DEFAULT;
	cmd->pipe_stream.err = DEFAULT;
	cmd->redir_stream.in = DEFAULT;
	cmd->redir_stream.out = DEFAULT;
	cmd->redir_stream.err = DEFAULT;
}

int	count_pipe(char	**argv)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (argv[++i])
		if (argv[i] == (char *)PIPE)
			count++;
	return (count);
}

//TODO: test
t_cmd	*split_pipe(char **argv, int len_cmd_table)
{
	t_cmd	*cmd_table;
	int		end;
	int		start;

	cmd_table = (t_cmd *)malloc(sizeof(t_cmd) * (len_cmd_table));
	if (!cmd_table)
		return (NULL);
	start = 0;
	end = -1;
	while (1)
	{
		end++;
		if (argv[end] == (char *)PIPE || argv[end] == NULL)
		{
			(*cmd_table).argv = argv + start;
			start = end + 1;
			init_cmd(cmd_table);
			if (argv[end] == NULL)
				break ;
			argv[end] = NULL;
			cmd_table++;
		}
	}
	cmd_table -= (len_cmd_table - 1);
	return (cmd_table);
}

int	make_pipe(t_cmd *cmd)
{
	pipe(cmd->pipe);
	return (0);
}

int	set_pipe_stream(t_cmd *cmd, t_cmd *next)
{
	cmd->pipe_stream.out = cmd->pipe[1];
	next->pipe_stream.in = cmd->pipe[0];
	return (0);
}

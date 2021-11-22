/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:22:01 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 00:05:43 by mishin           ###   ########.fr       */
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
	cmd->path = NULL;
	cmd->argv = NULL;
}

int	count_pipe(char	**argv)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (argv[++i])
		if (argv[i] == PIPE)
			count++;
	return (count);
}

static int	copy_args(char ***dst_ptr, char **src, int start, int end)
{
	int		i;
	char	**ret;

	ret = (char **)calloc_(end - start + 1, sizeof(char *));
	i = -1;
	while (++i < end - start)
	{
		if (is_empty(src[start + i]) || is_token(src[start + i]))
			ret[i] = src[start + i];
		else
			ret[i] = strdup_(src[start + i]);
	}
	*dst_ptr = ret;
	return (0);
}

t_cmd	*split_pipe(char **argv, int len_cmd_table)
{
	t_cmd	*cmd_table;
	int		end;
	int		start;

	cmd_table = (t_cmd *)calloc_(len_cmd_table, sizeof(t_cmd));
	start = 0;
	end = -1;
	while (1)
	{
		end++;
		if (argv[end] == PIPE || argv[end] == NULL)
		{
			init_cmd(cmd_table);
			copy_args(&(*cmd_table).argv, argv, start, end);
			start = end + 1;
			if (argv[end] == NULL)
				break ;
			cmd_table++;
		}
	}
	cmd_table -= (len_cmd_table - 1);
	return (cmd_table);
}

int	set_pipe_stream(t_cmd *cmd, t_cmd *next)
{
	pipe(cmd->pipe);
	cmd->pipe_stream.out = cmd->pipe[1];
	next->pipe_stream.in = cmd->pipe[0];
	return (0);
}

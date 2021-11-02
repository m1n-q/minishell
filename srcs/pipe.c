/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:22:01 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 16:39:36 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

static void	init_cmd(t_cmd *cmd)
{
	cmd->pipe[0] = 0;
	cmd->pipe[1] = 1;
	cmd->pipe_stream.in = -1;
	cmd->pipe_stream.out = -1;
	cmd->pipe_stream.err = -1;
	cmd->redir_stream.in = -1;
	cmd->redir_stream.out = -1;
	cmd->redir_stream.err = -1;
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
t_cmd	*split_pipe(char **argv, int *size)
{
	t_cmd	*cmd_table;
	int		num_pipe;
	int		argc;
	int		i_pipe;
	int		pos;

	argc = get_argc(argv);
	num_pipe = count_pipe(argv);
	*size = (num_pipe + 1);
	cmd_table = (t_cmd *)malloc(sizeof(t_cmd) * (num_pipe + 1));
	if (!cmd_table)
		return (NULL);
	if (num_pipe == 0)
	{
		cmd_table[0].argv = argv;
		init_cmd(cmd_table);
		return (cmd_table);
	}
	pos = 0;
	i_pipe = -1;
	while (1)
	{
		i_pipe++;
		if (argv[i_pipe] == (char *)PIPE || argv[i_pipe] == NULL)
		{
			/* method 1 */
			// (*cmd_table).argv = (char **)ft_calloc(i_pipe - pos + 1, sizeof(char *));
			// ft_memcpy((*cmd_table).argv, &argv[pos], (i_pipe - pos) * sizeof(char *));
			/* method 2 */
			(*cmd_table).argv = argv + pos;
			pos = i_pipe + 1;
			init_cmd(cmd_table);
			if (argv[i_pipe] == NULL)
				break ;
			argv[i_pipe] = NULL; /* method 2 */
			cmd_table++;
		}
	}
	cmd_table -= num_pipe;
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

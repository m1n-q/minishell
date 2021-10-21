/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:22:01 by mishin            #+#    #+#             */
/*   Updated: 2021/10/22 00:39:27 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

			(*cmd_table).io_table.stdin_fd = 0;
			(*cmd_table).io_table.stdout_fd = 1;
			(*cmd_table).io_table.stderr_fd = 2;
			(*cmd_table).pipe[0] = 0;
			(*cmd_table).pipe[1] = 1;


			if (argv[i_pipe] == NULL)
				break ;
			argv[i_pipe] = NULL;	/* method 2 */
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

int	connect_pipe(t_cmd to_be_in, t_cmd to_be_out)
{
	dup2(to_be_in.pipe[0], 0);
	close(to_be_in.pipe[1]);

	dup2(to_be_out.pipe[1], 1);
	close(to_be_out.pipe[0]);

	return (0);
}

int	set_pipe_stream(t_cmd *cmd, t_cmd *next)
{
	cmd->io_table.stdout_fd = cmd->pipe[1];
	next->io_table.stdin_fd = cmd->pipe[0];
	return (0);
}

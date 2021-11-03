/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:19:31 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 21:46:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_redir(t_cmd *cmd)
{
	int			i;
	int			count;

	count = 0;
	i = -1;
	while (cmd->argv[++i])
	{
		if (cmd->argv[i] == (char *)REDIRECT_OUT || \
			cmd->argv[i] == (char *)REDIRECT_IN || \
			cmd->argv[i] == (char *)REDIRECT_APPEND || \
			cmd->argv[i] == (char *)HEREDOC)
			count++;
	}
	return (count);
}

static int	check_redir(t_cmd *cmd)
{
	int			i;

	i = -1;
	while (cmd->argv[++i])
	{
		if ((cmd->argv[i] == (char *)REDIRECT_OUT || \
			cmd->argv[i] == (char *)REDIRECT_IN || \
			cmd->argv[i] == (char *)REDIRECT_APPEND || \
			cmd->argv[i] == (char *)HEREDOC) && \
			cmd->argv[i + 1])
		{
			if (cmd->argv[i] == (char *)REDIRECT_OUT)
				redir_out(cmd, cmd->argv[i + 1]);
			else if (cmd->argv[i] == (char *)REDIRECT_IN)
				redir_in(cmd, cmd->argv[i + 1]);
			else if (cmd->argv[i] == (char *)REDIRECT_APPEND)
				redir_append(cmd, cmd->argv[i + 1]);
			else if (cmd->argv[i] == (char *)HEREDOC)
				heredoc(cmd, cmd->argv[i + 1]);
			if (cmd->redir_stream.in == -1 || cmd->redir_stream.out == -1)
				return (-1);
		}
	}
	return (0);
}

static int	trim_redir(char ***argv, int count_redir)
{
	char	**new_argv;
	int		argc;
	int		i;
	int		j;

	argc = get_argc(*argv);
	new_argv = (char **)ft_calloc(argc - (count_redir * 2) + 1, sizeof(char *));
	if (!new_argv)
		return (-1);
	i = -1;
	j = -1;
	while ((*argv)[++i])
	{
		if ((*argv)[i] > (char *)10LL)
			new_argv[++j] = (*argv)[i];
		else
		{
			if ((*argv)[i + 1]) //TODO: test cases
				i += 1;
		}
	}
	(*argv) = new_argv;
	return (0);
}

int	check_cmd_table(t_cmd *cmd_table, int len_cmd_table)
{
	int	i;

	i = -1;
	while (++i < len_cmd_table)
	{
		if (check_redir(&cmd_table[i]) == -1)
			cmd_table[i].any_err = 1;
		trim_redir(&(cmd_table[i].argv), count_redir(&cmd_table[i]));
		set_path(&cmd_table[i]);
		if (i < len_cmd_table - 1)
		{
			make_pipe(&cmd_table[i]);
			set_pipe_stream(&cmd_table[i], &(cmd_table[i + 1]));
		}
	}
	return (0);
}

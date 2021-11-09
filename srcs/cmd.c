/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:19:31 by mishin            #+#    #+#             */
/*   Updated: 2021/11/09 16:08:43 by mishin           ###   ########.fr       */
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

static int	is_redir(char *arg)
{
	if (arg == (char *)REDIRECT_OUT || \
		arg == (char *)REDIRECT_IN || \
		arg == (char *)REDIRECT_APPEND || \
		arg == (char *)HEREDOC)
		return (1);
	return (0);
}

static int	check_redir(t_cmd *cmd)
{
	int	i;
	int	e;

	i = -1;
	while (cmd->argv[++i])
	{
		if (is_redir(cmd->argv[i]) && cmd->argv[i + 1])
		{
			if (cmd->argv[i] == (char *)REDIRECT_OUT)
				redir_out(cmd, cmd->argv[i + 1]);
			else if (cmd->argv[i] == (char *)REDIRECT_IN)
				redir_in(cmd, cmd->argv[i + 1]);
			else if (cmd->argv[i] == (char *)REDIRECT_APPEND)
				redir_append(cmd, cmd->argv[i + 1]);
			else if (cmd->argv[i] == (char *)HEREDOC)
			{
				e = heredoc(cmd, cmd->argv[i + 1]);
				if (e)
					return (e);
			}
			if (cmd->redir_stream.in == FDERR || cmd->redir_stream.out == FDERR)
				return (FDERR);
		}
	}
	return (0);
}

//TODO: test cases for line 81
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
			if ((*argv)[i + 1])
			{
				i += 1;
				free((*argv)[i]);
			}
		}
	}
	(*argv) = new_argv;
	return (0);
}

int	check_cmd_table(t_cmd *cmd_table, int len_cmd_table)
{
	int	i;
	int	e;

	i = -1;
	while (++i < len_cmd_table)
	{
		e = check_redir(&cmd_table[i]);
		{
			if (e == FDERR)
				cmd_table[i].any_err = 1;
			else if (e == HEREDOC_INTR)
				return (HEREDOC_INTR);
			else if (e == FORKERR)
				return (FORKERR);
		}
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

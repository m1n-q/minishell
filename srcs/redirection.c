/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:40:16 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/03 11:21:41 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

//NOTE: '>' 을 기준으로 쪼개서 run 해야 할 듯..

int	redir_in(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	return (fd);
}

int	redir_out(char *arg)
{
	int	fd;

	fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	redir_append(char *arg)
{
	int	fd;

	fd = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	check_redir(t_cmd *cmd, int *count_redir)
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
		{
			count++;
			if (cmd->argv[i + 1])
			{
				if (cmd->argv[i] == (char *)REDIRECT_OUT)
				{
					if (cmd->redir_stream.out != -1)
						close(cmd->redir_stream.out);
					cmd->redir_stream.out = redir_out(cmd->argv[i + 1]);
				}
				else if (cmd->argv[i] == (char *)REDIRECT_IN)		//NOTE: what if i == 0 and redir_in
				{
					if (cmd->redir_stream.in != -1)
						close(cmd->redir_stream.in);
					cmd->redir_stream.in = redir_in(cmd->argv[i + 1]);
				}
				else if (cmd->argv[i] == (char *)REDIRECT_APPEND)
				{
					if (cmd->redir_stream.out != -1)
						close(cmd->redir_stream.out);
					cmd->redir_stream.out = redir_append(cmd->argv[i + 1]);
				}
				else if (cmd->argv[i] == (char *)HEREDOC)
				{
					if (cmd->redir_stream.in != -1)
						close(cmd->redir_stream.in);
					cmd->redir_stream.in = heredoc(cmd->argv[i + 1]);
				}
			}
		}
	}
	*count_redir = count;
	return (0);
}

int	trim_redir(char ***argv, int count_redir)
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
		{
			new_argv[++j] = (*argv)[i];
		}
		else
		{
			if ((*argv)[i + 1])				//TODO: test cases
			{
				i += 1;
			}
		}
	}

	/* if pipe.method 2, free each cmd.argv*/
	// free((*argv));
	(*argv) = new_argv;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 14:30:04 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	run(t_cmd cmd)
{
	t_exit		ext;

	/* builtin without pipe (no fork) */
	get_or_set_interactive(SET, OFF);
	if (cmd.path != (char *)NOCMD && is_equal(cmd.path, "built-in") && \
		cmd.pipe_stream.in == -1 && cmd.pipe_stream.out == -1)					//FIXME: "built-in" can be input
	{
		connect_stream(cmd.redir_stream);
		if (is_equal("exit", cmd.argv[0]))
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			ext.pid = PARENT_EXIT;
			ext.status = 0;
			ext.code = __exit(cmd.argv);
		}
		else
		{
			ext.pid = BUILTIN;
			ext.status = 0;
			ext.code = run_builtin(cmd.argv);
		}
		return (ext);
	}

	ext.pid = fork();
	ext.status = 0;
	ext.code = 0;
	if (ext.pid < 0)
		printf("fork failed\n");

	if (ext.pid == CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		connect_stream(cmd.pipe_stream);
		connect_stream(cmd.redir_stream);
		if (cmd.path == NULL)
		{
			internal_error(cmd.argv[0], "command not found");
			ext.code = EX_NOTFOUND;
		}
		else if (cmd.path == (char *)NOCMD)
			ext.code = 0;
		else if (is_equal(cmd.path, "built-in"))
		{
			if (is_equal("exit", cmd.argv[0]))
			{
				ext.status = 0;
				ext.code = __exit(cmd.argv);
				if (ext.code == E2MANY)
					ext.code = EXECUTION_FAILURE;
			}
			else
			{
				ext.status = 0;
				ext.code = run_builtin(cmd.argv);
			}
		}
		else if (execve(cmd.path, cmd.argv, environ) == -1)
			ext.code = check_error(cmd.argv[0]);
	}

	else if (ext.pid > 0)
	{
		destroy_stream(cmd.pipe_stream);
		destroy_stream(cmd.redir_stream);
		ext.pid = wait(&ext.status);		//FIXIT: have to be async
	}

	return (ext);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 01:50:28 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	builtin_nofork(t_cmd cmd)
{
	t_exit	ext;

	connect_stream(cmd.redir_stream);
	if (is_equal("exit", cmd.argv[0]))
	{
		ext.pid = PARENT_EXIT;
		ext.status = 0;
		ext.code = __exit(cmd, PARENT_EXIT);
	}
	else
	{
		ext.pid = BUILTIN;
		ext.status = 0;
		ext.code = run_builtin(cmd);
	}
	return (ext);
}

t_exit	builtin_fork(t_cmd cmd)
{
	t_exit	ext;

	ext.pid = CHILD;
	if (is_equal("exit", cmd.argv[0]))
	{
		ext.status = 0;
		ext.code = __exit(cmd, CHILD);
		if (ext.code == E2MANY)
			ext.code = EXECUTION_FAILURE;
	}
	else
	{
		ext.status = 0;
		ext.code = run_builtin(cmd);
	}
	return (ext);
}

/*
	• cmd.path == NULL: command not found
	• cmd.path == NOCMD: only redir w/o command
	• built-in in forked process
	• execve
	• if execve fail
*/
t_exit	child(t_cmd cmd)
{
	t_exit	ext;

	ext.pid = CHILD;
	ext.status = 0;
	signal(SIGQUIT, SIG_DFL);
	sig_jobcontrol(ON);
	connect_stream(cmd.pipe_stream);
	connect_stream(cmd.redir_stream);
	if (cmd.path == NULL)
	{
		internal_error(cmd.argv[0], "command not found");
		ext.code = EX_NOTFOUND;
	}
	else if (cmd.path == NOCMD)
		ext.code = 0;
	else if (is_equal(cmd.path, "built-in"))
		ext = builtin_fork(cmd);
	else if (execve(cmd.path, cmd.argv, environ) == -1)
		ext.code = check_error(cmd.argv[0]);
	return (ext);
}

t_exit	run(t_cmd cmd)
{
	t_exit		ext;

	get_or_set_interactive(SET, OFF);
	settty(ON, ECHOCTL);
	if (cmd.any_err)
		return ((t_exit){-1, 0, EXECUTION_FAILURE});
	if (cmd.path != NOCMD && is_equal(cmd.path, "built-in") && \
		cmd.pipe_stream.in == DEFAULT && cmd.pipe_stream.out == DEFAULT)
		return (builtin_nofork(cmd));
	ext.pid = fork();
	ext.status = 0;
	ext.code = 0;
	if (ext.pid < 0)
	{
		ft_putendl_fd("fork failed\n", STDERR_FILENO);
		return ((t_exit){-1, 0, EXECUTION_FAILURE});
	}
	else if (ext.pid > 0)
	{
		destroy_stream(cmd.pipe_stream);
		destroy_stream(cmd.redir_stream);
	}
	else if (ext.pid == CHILD)
		ext = child(cmd);
	return (ext);
}

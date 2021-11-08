/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 19:49:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FIXME: "built-in" can be input
t_exit	builtin_nofork(t_cmd cmd)
{
	t_exit	ext;

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

t_exit	builtin_fork(t_cmd cmd)
{
	t_exit	ext;

	ext.pid = CHILD;
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
	return (ext);
}

/*
	• command not found
	• only redir w/o command
	• built-in in forked process
	• execve
	• execve fail
*/
t_exit	c(t_cmd cmd)
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
	else if (cmd.path == (char *)NOCMD)
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
	if (cmd.path != (char *)NOCMD && is_equal(cmd.path, "built-in") && \
		cmd.pipe_stream.in == DEFAULT && cmd.pipe_stream.out == DEFAULT)
		return (builtin_nofork(cmd));
	ext.pid = fork();
	ext.status = 0;
	ext.code = 0;
	if (ext.pid < 0)
		printf("fork failed\n");
	else if (ext.pid > 0)
	{
		destroy_stream(cmd.pipe_stream);
		destroy_stream(cmd.redir_stream);
	}
	else if (ext.pid == CHILD)
		ext = c(cmd);
	return (ext);
}

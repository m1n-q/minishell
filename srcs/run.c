/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/22 22:07:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	1. If the command contains no slashes
		1-1. shell function
		1-2. corresponding built-in command
		1-3. searches $PATH for an executable

	2. If the command contains slashes, that named file is executed.
*/

t_exit	run(t_cmd cmd)
{
	t_exit		ext;

	if (is_equal(cmd.path, "built-in"))		//FIXME: "built-in" can be input
	{
		if (is_equal("exit", cmd.argv[0]))
			return ((t_exit){PARENT_EXIT, __exit(cmd.argv)});
		else
			return ((t_exit){BUILTIN, run_builtin(cmd.argv)});
	}

	ext.pid = fork();
	ext.status = 0;
	if (ext.pid < 0)
		printf("fork failed\n");

	if (ext.pid == CHILD)
	{
		signal(SIGINT, sig_handler_child);
		signal(SIGQUIT, sig_handler_child);
		connect_stream(cmd.pipe_stream);
		connect_stream(cmd.redir_stream);
		if (execve(cmd.path, cmd.argv, environ) == -1)			/* if has slash and execve fail -> No such file or directory */
			ext.status = errno;		//FIXIT: clarify name & usage: status / exitcode
	}

	else if (ext.pid > 0)
	{
		destroy_stream(cmd.pipe_stream);
		destroy_stream(cmd.redir_stream);
		ext.pid = wait(&ext.status);
	}

	return (ext);
}


// return ((t_exit){BUILTIN, ENOCMD});				/* Command not found */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 22:36:15 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	run(t_cmd cmd)
{
	t_exit		ext;

	if (is_equal(cmd.path, "built-in"))		//FIXME: "built-in" can be input
	{
		if (is_equal("exit", cmd.argv[0]))
			return ((t_exit){PARENT_EXIT, 0, __exit(cmd.argv)});
		else
			return ((t_exit){BUILTIN, 0, run_builtin(cmd.argv)});
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

/*
	BUILTIN
		pass;


	if (has slash) {
		if (is_exist) {
			if (is_dir) {
				is a directory (126 EX_NOEXEC)
			}
			else if (is_text or sth) {
				Permission denied (return errno => EACCES)
			}
			else {

			}

		}

		else {
			No such file or directory (127)
		}
	}
	else {
		if (cmd.path == NULL)  ~ not in $PATH {
			command not found (127)
		}
		else {
			if (!success)
				errno from execve
		}
	}


*/

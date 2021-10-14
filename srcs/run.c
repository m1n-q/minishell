/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/14 21:05:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NOTE: '>' 을 기준으로 쪼개서 run 해야 할 듯..
// int	split(t_cmd cmd);
// {
// 	if (PIPE || REDIRECT_IN || REDIRECT_OUT || REDIRECT_APPEND || HEREDOC)
// 	{
// 		if (PIPE)
// 			run argv till PIPE and pipe()
// 		else if (REDIRECT_OUT || REDIRECT_APPEND)
// 			run argv till REDIRECT_OUT and redirect_out(after REDIRECT_OUT)
// 		else if (REDIRECT_IN)
// 			redirect_in(after REDIRECT_IN) and run argv till REDIRECT_IN
// 	}
// 	restore_stream();
// }

/*
	1. If the command contains no slashes
		1-1. shell function
		1-2. corresponding built-in command
		1-3. searches $PATH for an executable

	2. If the command contains slashes, that named file is executed.
*/

//FIXIT: if (!slashes) { built-in -> PATH } else {excute argv}
static int has_slash(char *arg)
{
	if (ft_strchr(arg, '/'))
		return (1);
	return (0);
}

t_exit	run(t_cmd cmd)
{
	t_exit		ext;

	if (!cmd.path)
	{
		if (ft_strlen(cmd.argv[0]) == 4 && !ft_strncmp(cmd.argv[0], "exit", 4))
			return ((t_exit){PARENT_EXIT, __exit(cmd.argv)});
		else if (is_builtin(cmd.argv[0]))
			return ((t_exit){BUILTIN, run_builtin(cmd.argv)});
		else
		{
			if (has_slash(cmd.argv[0]))
				cmd.path = cmd.argv[0];
			else
				return ((t_exit){BUILTIN, ENOCMD});				/* Command not found */
		}
	}
	ext.pid = fork();
	ext.status = 0;
	if (ext.pid == CHILD)
	{
		if (execve(cmd.path, cmd.argv, environ) == -1)			/* if has slash and execve fail -> No such file or directory */
			ext.status = errno;
	}
	else if (ext.pid > 0)
		ext.pid = wait(&ext.status);
	return (ext);
}

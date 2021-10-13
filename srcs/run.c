/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 15:36:40 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run(t_cmd cmd)
{
	extern char	**environ;
	int			pid;
	int			status;

	if (!cmd.path)
	{
		if (is_builtin(cmd.argv[0]))
			return (run_builtin(cmd.argv) + BUILTIN);	/* To notify that it isn't a child process */
		else
			return (ENOENT);							/* No such file or directory */
	}
	pid = fork();
	if (!pid)											/* child process */
		execve(cmd.path, cmd.argv, environ);
	else if (pid > 0)
		wait(&status);
	return (pid);
}

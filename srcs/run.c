/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/12 20:23:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	run(t_cmd cmd)
{
	extern char	**environ;
	int			pid;
	int			status;

	if (!cmd.path)
		return (ENOENT);	/* No such file or directory */
	pid = fork();
	if (!pid)				/* child process */
		execve(cmd.path, cmd.argv, environ);
	else if (pid > 0)
		wait(&status);
	return (pid);
}

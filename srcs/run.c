/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 19:08:39 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exit	run(t_cmd cmd)
{
	extern char	**environ;
	t_exit		ext;

	if (!cmd.path)
	{
		if (!ft_strncmp(cmd.argv[0], "exit", ft_strlen(cmd.argv[0])))
			return ((t_exit){PARENT_EXIT, __exit(cmd.argv)});
		else if (is_builtin(cmd.argv[0]))
			return ((t_exit){PARENT, run_builtin(cmd.argv)});
		else
			return ((t_exit){PARENT, ENOENT});				/* No such file or directory */
	}
	ext.pid = fork();
	if (!ext.pid)											/* child process */
		execve(cmd.path, cmd.argv, environ);
	else if (ext.pid > 0)
		ext.pid = wait(&ext.status);
	return (ext);
}

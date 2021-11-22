/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:30:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 00:05:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_empty_vars(t_cmd cmd, int cur)
{
	int	i;

	i = cur;
	while (++i < cmd.argc)
		if (cmd.argv[i])
			break ;
	if (i > cmd.argc)
		i = cmd.argc;
	return (i);
}

int	is_builtin(char *arg)
{
	if (is_equal(arg, "cd") || \
		is_equal(arg, "pwd") || \
		is_equal(arg, "env") || \
		is_equal(arg, "echo") || \
		is_equal(arg, "exit") || \
		is_equal(arg, "unset") || \
		is_equal(arg, "export"))
		return (1);
	return (0);
}

int	run_builtin(t_cmd cmd)
{
	if (is_equal(cmd.argv[0], "cd"))
		return (__cd(cmd));
	if (is_equal(cmd.argv[0], "pwd"))
		return (__pwd(cmd));
	if (is_equal(cmd.argv[0], "env"))
		return (__env(cmd));
	if (is_equal(cmd.argv[0], "echo"))
		return (__echo(cmd));
	if (is_equal(cmd.argv[0], "unset"))
		return (__unset(cmd));
	if (is_equal(cmd.argv[0], "export"))
		return (__export(cmd));
	return (0);
}

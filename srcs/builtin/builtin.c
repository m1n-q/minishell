/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:30:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 20:40:28 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NOTE: in bash, echo & pwd could get sh_wrerror (ferror(stdout))
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

int	run_builtin(char **argv)
{
	if (is_equal(argv[0], "cd"))
		return (__cd(argv));
	if (is_equal(argv[0], "pwd"))
		return (__pwd(argv));
	if (is_equal(argv[0], "env"))
		return (__env(argv));
	if (is_equal(argv[0], "echo"))
		return (__echo(argv));
	if (is_equal(argv[0], "unset"))
		return (__unset(argv));
	if (is_equal(argv[0], "export"))
		return (__export(argv));
	return (0);
}

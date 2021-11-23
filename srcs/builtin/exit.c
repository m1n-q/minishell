/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:49 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 15:05:05 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_exit(void)
{
	static_stream(DESTROY);
	__siglist(DESTROY, 0);
	settty(RESTORE, 0);
	free_till(get_argc(environ), environ);
	free(environ);
}

int	__exit(t_cmd cmd, int is)
{
	int			exit_code;
	int			i;
	intmax_t	retval;

	exit_code = 0;
	retval = 0;
	if (is == PARENT_EXIT)
		ft_putendl_fd("exit", STDERR_FILENO);
	i = skip_empty_vars(cmd, 0);
	if (cmd.argv[i])
	{
		if (legal_number(cmd.argv[i], &retval) == 0)
		{
			sh_neednumarg(cmd.argv[0], cmd.argv[i]);
			return (255);
		}
	}
	i = skip_empty_vars(cmd, i);
	if (cmd.argv[i])
	{
		builtin_error(cmd.argv[0], NULL, "too many arguments", 0);
		return (E2MANY);
	}
	exit_code = retval & 255;
	return (exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:49 by mishin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/22 22:23:46 by kyumlee          ###   ########.fr       */
=======
/*   Updated: 2021/11/22 22:34:09 by mishin           ###   ########.fr       */
>>>>>>> c910b26b819ca744133bc366575d7d0d2fff83c5
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	before_exit(void)
{
	static_stream(DESTROY);
	settty(RESTORE, 0);
	free_till(get_argc(environ), environ);
	free(environ);
}

int	__exit(t_cmd cmd)
{
	int			exit_code;
	int			i;
	intmax_t	retval;

	exit_code = 0;
	retval = 0;
	i = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	i = skip_empty_vars(cmd, i);
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

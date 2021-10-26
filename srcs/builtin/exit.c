/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:49 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 23:01:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NOTE: case (argv[1] == NULL): NULL cannot be argument in minishell
int __exit(char **argv)
{
	int			exit_code;
	int			argc;
	intmax_t	retval;

	argc = get_argc(argv);
	exit_code = 0;
	if (argv[1])
	{
		if (legal_number(argv[1], &retval) == 0)			/* exit: string: numeric argument required */
		{
			sh_neednumarg(argv[0], argv[1]);
			return (255);
		}
	}
	if (argc > 2)
	{
		builtin_error(argv[0], NULL, "too many arguments");
		return (-1);
	}
	exit_code = retval & 255;
	return (exit_code);
}

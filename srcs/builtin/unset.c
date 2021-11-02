/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:54 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 21:04:19 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	if (var && !unset_function && non_unsettable_p (var))
		builtin_error (_("%s: cannot unset"), name);
	if (var && readonly_p (var))
		builtin_error (_("%s: cannot unset: readonly %s",
						name, unset_function ? "function" : "variable")

	=> no (readonly || non_unsettable) var in minishell.
*/
int	__unset(char **argv)
{
	t_envent	env;
	int			i;

	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);	/* do not allow any option */
			return (EXECUTION_FAILURE);
		}
	}
	i = 0;
	while (argv[++i])
	{
		env = find_envent(argv[i]);
		remove_envent(env);
	}
	return (0);
}

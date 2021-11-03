/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:54 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 23:30:40 by mishin           ###   ########.fr       */
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
	int			any;

	i = 0;
	any = 0;
	if (argv[1] && isoption(argv[1], TIL_END))
	{
		sh_invalidopt(argv[0], argv[1]);
		builtin_usage(argv[0], UNSET_SHORTDOC);
		return (EX_BADUSAGE);
	}
	while (argv[++i])
	{
		if (legal_identifier(argv[i]) == 0)
		{
			sh_invalidid(argv[0], argv[i]);
			any = EXECUTION_FAILURE;
			continue ;
		}
		env = find_envent(argv[i]);
		remove_envent(env);
	}
	return (any);
}

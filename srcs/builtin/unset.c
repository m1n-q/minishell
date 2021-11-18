/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:54 by mishin            #+#    #+#             */
/*   Updated: 2021/11/18 15:47:21 by mishin           ###   ########.fr       */
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
int	__unset(t_cmd cmd)		//TODO : test EMPTY_VAR
{
	t_envent	entry;
	int			i;
	int			any;

	any = 0;
	i = skip_empty_vars(cmd, 0);
	if (cmd.argv[i] && isoption(cmd.argv[i], TIL_END))
	{
		sh_invalidopt(cmd.argv[0], cmd.argv[i]);
		builtin_usage(cmd.argv[0], UNSET_SHORTDOC);
		return (EX_BADUSAGE);
	}
	while (i < cmd.argc)
	{
		if (cmd.argv[i] == NULL)
		{
			i = skip_empty_vars(cmd, i);
			continue ;
		}
		if (legal_identifier(cmd.argv[i]) == 0)
		{
			sh_invalidid(cmd.argv[0], cmd.argv[i]);
			any = EXECUTION_FAILURE;
			i = skip_empty_vars(cmd, i);
			continue ;
		}
		entry = find_envent(cmd.argv[i]);
		remove_envent(entry);
		free_envent(entry);
		i = skip_empty_vars(cmd, i);
	}
	return (any);
}

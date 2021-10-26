/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:54 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:43:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	if (var && !unset_function && non_unsettable_p (var))
		builtin_error (_("%s: cannot unset"), name);
	if (var && readonly_p (var))
		builtin_error (_("%s: cannot unset: readonly %s", name, unset_function ? "function" : "variable")

	=> no (readonly || non_unsettable) var in minishell.
*/
//TODO: getopt and handle
int	__unset(char **argv)
{
	t_envent	env;
	int			i;

	if (!argv || !*argv)
		return (-1);
	i = 0;
	while (argv[++i])
	{
		env = get_envent(argv[i]);
		remove_envent(env);
	}
	return (0);
}

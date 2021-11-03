/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:47:16 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 19:57:19 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	unbind_var(char *arg, int *aflag)
{
	t_var	newvar;
	int		assign_pos;

	assign_pos = get_assign_pos(arg);
	if (assign_pos)
	{
		arg[assign_pos] = '\0';
		if (arg[assign_pos - 1] == '+')
		{
			if (aflag != NULL)
				(*aflag)++;
			arg[assign_pos - 1] = '\0';
		}
	}
	newvar.name = arg;
	if (assign_pos)
		newvar.value = arg + assign_pos + 1;
	else
		newvar.value = NULL;
	return (newvar);
}

char	*bind_var(t_var var, int assign_pos, int *aflag)
{
	if (assign_pos)
	{
		var.name[assign_pos] = '=';
		if (aflag && *aflag)
			var.name[assign_pos - 1] = '+';
	}
	return (var.name);
}

/* Note that '=' at the start of a word is not an assignment statement. */
int	get_assign_pos(const char *string)
{
	register int	idx;

	idx = 0;
	if (legal_variable_starter(string[idx]) == 0)
		return (0);
	while (string[idx])
	{
		if (string[idx] == '=')
			return (idx);
		if (string[idx] == '+' && string[idx + 1] == '=')
			return (idx + 1);
		if (legal_variable_char(string[idx]) == 0)
			return (0);
		idx++;
	}
	return (0);
}

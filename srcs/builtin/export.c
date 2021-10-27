/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:24 by mishin            #+#    #+#             */
/*   Updated: 2021/10/27 18:59:18 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_including_empty(void)
{
	int			i;

	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);				/* Only 'NAME'='VAL' */
	return (0);
}

int check_name_part(char *arg, int assign_pos, int *aflag)
{
	t_var	var;
	int		error;

	error = 0;
	var = unbind_var(arg, aflag);
	if (!legal_identifier(var.name))
	{
		sh_invalidid("export", var.name);
		if (assign_pos)
			error = EX_BADASSIGN;
		else
			error = EXECUTION_FAILURE;
	}
	bind_var(var, assign_pos, aflag);
	return (error);
}

/*
	free(env.name);
	free(env.value);
	env.string was equal to environ[i]
*/
int	assign_or_just_add(char *arg, int append)
{
	t_envent	entry;
	t_var		newvar;
	int			assign;
	char		*tmpval;

	assign = get_assign_pos(arg);
	newvar = unbind_var(arg, NULL);
	entry = find_envent(newvar.name);
	if (entry.string)
	{
		if (assign)								/* if exists && assign : modify existing entry */
		{
			if (append)							/* if append flag */
			{
				tmpval = ft_strjoin(entry.value, newvar.value);
				remove_envent(entry);
				add_envent(entry.name, tmpval);
			}
			else
			{
				remove_envent(entry);
				add_envent(newvar.name, newvar.value);
			}
		}
		else
			return (EXECUTION_SUCCESS);			/* if exists && ~assign : ignore */
	}
	else
	{
		if (assign)								/* if new && assign : append new entry */
		{
			if (append)
			{
				add_envent(newvar.name, newvar.value);
			}
			else
			{
				add_envent(newvar.name, newvar.value);
			}
		}
		else									/* if new && ~assign : append new entry w/o '='  */
		{
			add_envent(newvar.name, newvar.value);
		}
	}
	return (EXECUTION_SUCCESS);
}

int	export_internal(char *arg)
{
	int			asspos;
	int			aflag;
	int			error;

	aflag = 0;
	asspos = get_assign_pos(arg);
	error = check_name_part(arg, asspos, &aflag);

	assign_or_just_add(arg, aflag);


	/* when list, it is precedence of return value */
	if (error == EX_BADASSIGN)
		return (EX_BADASSIGN);
	else if (error == EXECUTION_FAILURE)	// if any error=1
		return (EXECUTION_FAILURE);
	return (EXECUTION_SUCCESS);
}

//TODO: getopt and handle
int	__export(char **argv)
{
	int		i;
	int		argc;

	argc = get_argc(argv);
	if (argc == 1)
		return (print_including_empty());			/* print including just 'name' */

	i = 0;
	while (argv[++i])
		if (!export_internal(argv[i]))
			// g_exit_code = EXECUTION_FAILURE;
			;
	return (0);
}

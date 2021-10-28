/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:24 by mishin            #+#    #+#             */
/*   Updated: 2021/10/28 21:35:26 by mishin           ###   ########.fr       */
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
	if (error)
		return (error);
	assign_or_just_add(arg, aflag);

	/* when list, it is precedence of return value */
	/*
		return (assign_error ? EX_BADASSIGN
						: ((any_failed == 0) ? EXECUTION_SUCCESS
												: EXECUTION_FAILURE));
	*/
	return (EXECUTION_SUCCESS);
}

int	__export(char **argv)
{
	int		i;
	int		argc;
	int		tmp;
	int		error;

	error = 0;
	tmp = 0;
	argc = get_argc(argv);
	if (argc == 1)
		return (print_including_empty());			/* print including just 'name' */

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
		tmp = export_internal(argv[i]);
		if (tmp > error)
			error = tmp;
	}
	return (error);
}

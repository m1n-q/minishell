/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:24 by mishin            #+#    #+#             */
/*   Updated: 2021/11/09 18:06:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_including_empty(void)
{
	int		i;
	char	c;
	char	*x;
	t_var	var;
	char	**tmp_environ;

	c = 'x';
	tmp_environ = make_tmp_environ();
	quick_sort(tmp_environ, 0, get_argc(tmp_environ) - 1);
	i = -1;
	while (tmp_environ[++i])
	{
		printf ("declare -%c ", c);
		var = unbind_var(tmp_environ[i], NULL);
		x = sh_double_quote(var.value);
		if (var.value)
			printf("%s=%s\n", var.name, x);
		else
			printf("%s\n", var.name);
		free(x);
	}
	free_till(get_argc(tmp_environ), tmp_environ);
	free(tmp_environ);
	return (0);
}

int	check_name_part(char *arg, int assign_pos, int *aflag)
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

/* entry.string == environ[i]: no need to free */
/* entry.string != NULL: entry exists in environ */
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
		if (assign && append)
		{
			if (entry.value)
				tmpval = ft_strjoin(entry.value, newvar.value);
			else
				tmpval = ft_strdup(newvar.value);
			remove_envent(entry);
			add_envent(entry.name, tmpval);
			free(tmpval);
		}
		else if (assign)
		{
			remove_envent(entry);
			add_envent(newvar.name, newvar.value);
		}
	}
	else
		add_envent(newvar.name, newvar.value);
	free_envent(entry);
	return (EXECUTION_SUCCESS);
}

/* when list, it is precedence of return value */
/*
	return (assign_error ? EX_BADASSIGN
					: ((any_failed == 0) ? EXECUTION_SUCCESS
											: EXECUTION_FAILURE));
*/
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
	return (EXECUTION_SUCCESS);
}

int	__export(char **argv)
{
	int		i;
	int		tmp;
	int		error;

	error = 0;
	tmp = 0;
	if (get_argc(argv) == 1)
		return (print_including_empty());
	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);
			builtin_usage(argv[0], EXPORT_SHORTDOC);
			return (EX_BADUSAGE);
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

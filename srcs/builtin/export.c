/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:24 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 21:06:51 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_double_quote(char *string)
{
	int		i;
	char	*ret;

	if (!string)
		return (NULL);
	ret = (char *)ft_calloc(ft_strlen(string) + 3, sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '"';
	i = -1;
	while (string[++i])
		ret[i + 1] = string[i];
	ret[i + 1] = '"';
	return (ret);
}

char	**make_tmp_environ(void)
{
	char	**tmp_environ;
	int		i;

	tmp_environ = (char **)ft_calloc(get_argc(environ) + 1, sizeof(char *));
	if (!tmp_environ)
		return (NULL);
	i = -1;
	while (environ[++i])
		tmp_environ[i] = ft_strdup(environ[i]);
	return (tmp_environ);
}

void	quick_sort(char	**arr, int start, int end)
{
	int		p;
	int		l;
	int		r;
	char	*tmp;

	if (end - start + 1 <= 1)
		return ;
	p = end;
	l = start;
	r = end - 1;
	while (l < r)
	{
		while (l < end && ft_strncmp(arr[l], arr[p], ft_strlen(arr[p])) < 0)
			l++;
		while (r > 0 && ft_strncmp(arr[r], arr[p], ft_strlen(arr[p])) > 0)
			r--;
		if (l < r)
		{
			tmp = arr[l];
			arr[l] = arr[r];
			arr[r] = tmp;
		}
	}
	tmp = arr[l];
	arr[l] = arr[p];
	arr[p] = tmp;
	quick_sort(arr, 0, l - 1);
	quick_sort(arr, l + 1, end);
}

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
	}
	i = -1;
	while (tmp_environ[++i])
		free(tmp_environ[i]);
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
		add_envent(newvar.name, newvar.value);
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

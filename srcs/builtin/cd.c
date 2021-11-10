/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:33 by mishin            #+#    #+#             */
/*   Updated: 2021/11/10 16:34:20 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bindpwd(char *oldpwd)
{
	char	*tmp;
	char	*otmp;

	otmp = strjoin_("OLDPWD=", oldpwd);
	tmp = strjoin_("PWD=", getcwd(NULL, 0));
	export_internal(tmp);
	export_internal(otmp);
	free(tmp);
	free(otmp);
	return (EXECUTION_SUCCESS);
}

static int	check_option(char **argv)
{
	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);
			builtin_usage(argv[0], CD_SHORTDOC);
			return (EXECUTION_FAILURE);
		}
		return (0);
	}
	return (0);
}

static int	check_arg(char **argv, char **dirname)
{
	if (argv[1] == NULL)
	{
		*dirname = getenv("HOME");
		if (!*dirname)
		{
			builtin_error(argv[0], NULL, "HOME not set", 0);
			return (EXECUTION_FAILURE);
		}
		return (0);
	}
	else if (is_equal(argv[1], "-"))
	{
		*dirname = getenv("OLDPWD");
		if (!*dirname)
		{
			builtin_error(argv[0], NULL, "OLDPWD not set", 0);
			return (EXECUTION_FAILURE);
		}
		printf("%s\n", *dirname);
		return (0);
	}
	else
		*dirname = argv[1];
	return (0);
}

int	__cd(char **argv)
{
	char	*dirname;
	char	*cwd;

	if (check_option(argv) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	if (check_arg(argv, &dirname) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	cwd = getcwd(NULL, 0);
	if (chdir(dirname) == 0)
		return (bindpwd(cwd));
	builtin_error(argv[0], dirname, strerror(errno), 0);
	return (EXECUTION_FAILURE);
}

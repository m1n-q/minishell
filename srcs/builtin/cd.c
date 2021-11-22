/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:33 by mishin            #+#    #+#             */
/*   Updated: 2021/11/22 22:41:37 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bindpwd(char *oldpwd)
{
	char	*tmp;
	char	*otmp;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	otmp = strjoin_("OLDPWD=", oldpwd);
	tmp = strjoin_("PWD=", pwd);
	free(pwd);
	free(oldpwd);
	export_internal(tmp);
	export_internal(otmp);
	free(tmp);
	free(otmp);
	return (EXECUTION_SUCCESS);
}

static int	check_option(t_cmd cmd)
{
	int	i;

	i = skip_empty_vars(cmd, 0);
	if (cmd.argv[i])
	{
		if (isoption(cmd.argv[i], TIL_END))
		{
			sh_invalidopt(cmd.argv[0], cmd.argv[i]);
			builtin_usage(cmd.argv[i], CD_SHORTDOC);
			return (EXECUTION_FAILURE);
		}
		return (0);
	}
	return (0);
}

static int	check_arg(t_cmd cmd, char **dirname)
{
	int	i;

	i = skip_empty_vars(cmd, 0);
	if (cmd.argv[i] == NULL || is_equal(cmd.argv[i], "~"))
	{
		*dirname = getenv("HOME");
		if (!*dirname)
		{
			builtin_error(cmd.argv[0], NULL, "HOME not set", 0);
			return (EXECUTION_FAILURE);
		}
	}
	else if (is_equal(cmd.argv[i], "-"))
	{
		*dirname = getenv("OLDPWD");
		if (!*dirname)
		{
			builtin_error(cmd.argv[0], NULL, "OLDPWD not set", 0);
			return (EXECUTION_FAILURE);
		}
		printf("%s\n", *dirname);
	}
	else
		*dirname = cmd.argv[i];
	return (0);
}

int	__cd(t_cmd cmd)
{
	char	*dirname;
	char	*cwd;

	if (check_option(cmd) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	if (check_arg(cmd, &dirname) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	cwd = getcwd(NULL, 0);
	if (chdir(dirname) == 0)
		return (bindpwd(cwd));
	free(cwd);
	builtin_error(cmd.argv[0], dirname, strerror(errno), 0);
	return (EXECUTION_FAILURE);
}

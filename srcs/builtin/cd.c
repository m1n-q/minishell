/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:33 by mishin            #+#    #+#             */
/*   Updated: 2021/10/28 19:53:33 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cd: usage: cd [dir]
*/

int	bindpwd(char *oldpwd)
{
	char	*tmp;
	char	*otmp;

	otmp = ft_strjoin("OLDPWD=", oldpwd);
	tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
	export_internal(tmp);
	export_internal(otmp);
	free(tmp);
	free(otmp);
	return (EXECUTION_SUCCESS);
}

//NOTE: CDPATH
int	__cd(char **argv)
{
	char	*dirname;
	char	*cwd;

	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);	/* do not allow any option */
			return (EXECUTION_FAILURE);
		}
	}

	cwd = getcwd(NULL, 0);
	if (argv[1] == NULL)
	{
		dirname = getenv("HOME");
		if (!dirname)
		{
			builtin_error(argv[0], NULL, "HOME not set", 0);
			return (EXECUTION_FAILURE);
		}
	}
	else if (is_equal(argv[1], "-"))
	{
		dirname = getenv("OLDPWD");
		if (!dirname)
		{
			builtin_error(argv[0], NULL, "OLDPWD not set", 0);
			return (EXECUTION_FAILURE);
		}
		printf("%s\n", dirname);
	}
	else
		dirname = argv[1];

	if (chdir(dirname) == 0)
		return (bindpwd(cwd));

	builtin_error(argv[0], dirname, strerror(errno), 0);
	return (EXECUTION_FAILURE);
}

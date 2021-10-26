/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:33 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:40:21 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bindpwd(char *oldpwd)
{
	char	*tmp;
	char	*otmp;

	otmp = ft_strjoin("OLDPWD=", oldpwd);
	tmp = ft_strjoin("PWD=", getcwd(NULL, 0));
	check_arg(tmp);
	check_arg(otmp);
	free(tmp);
	free(otmp);
	return (EXECUTION_SUCCESS);
}

//NOTE: CDPATH
int	__cd(char **argv)
{
	char	*dirname;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (argv[1] == NULL)
	{
		dirname = getenv("HOME");
		if (!dirname)
		{
			builtin_error(argv[0], NULL, "HOME not set");
			return (EXECUTION_FAILURE);
		}
	}
	else if (is_equal(argv[1], "-"))
	{
		dirname = getenv("OLDPWD");
		if (!dirname)
		{
			builtin_error(argv[0], NULL, "OLDPWD not set");
			return (EXECUTION_FAILURE);
		}
		printf("%s\n", dirname);
	}
	else
		dirname = argv[1];

	if (chdir(dirname) == 0)
		return (bindpwd(cwd));

	builtin_error(argv[0], dirname, strerror(errno));
	return (EXECUTION_FAILURE);
}

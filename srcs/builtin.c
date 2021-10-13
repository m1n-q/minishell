/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:30:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 15:34:20 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ env with no options or arguments
◦ echo with option -n
◦ exit with no options
◦ unset with no options
◦ export with no options
*/

//NOTE: need to handle additional (not supported) args

int	is_builtin(char *arg)
{
	if (!ft_strncmp(arg, "cd", 2) || \
		!ft_strncmp(arg, "pwd", 3) || \
		!ft_strncmp(arg, "env", 3) || \
		!ft_strncmp(arg, "echo", 4) || \
		!ft_strncmp(arg, "exit", 4) || \
		!ft_strncmp(arg, "unset", 5) || \
		!ft_strncmp(arg, "export", 6))
		return (1);
	return (0);
}

int	cd(char **argv)
{
	char	*home;

	if (argv[1] == NULL)
	{
		home = getenv("HOME");
		if (!home)
			return (0);
		else
			chdir(home);
	}
	else
	{
		if (chdir(argv[1]) == -1)
			return (errno);
	}
	return (0);
}

int	pwd(char **argv)
{
	char	*cwd;

	(void)argv;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errno);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	run_builtin(char **argv)
{
	if (!ft_strncmp(argv[0], "cd", 2))
		return (cd(argv));
	if (!ft_strncmp(argv[0], "pwd", 3))
		return (pwd(argv));
	// if (!ft_strncmp(argv[0], "env", 3))
	// 	return (env(argv));
	// if (!ft_strncmp(argv[0], "exit", 4))
	// 	return (exit(argv));
	// if (!ft_strncmp(argv[0], "echo", 4))
	// 	return (echo(argv));
	// if (!ft_strncmp(argv[0], "unset", 5))
	// 	return (unset(argv));
	// if (!ft_strncmp(argv[0], "export", 6))
	// 	return (export(argv));
	return (0);
}

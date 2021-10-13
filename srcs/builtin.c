/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:30:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 20:19:55 by mishin           ###   ########.fr       */
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

int	__cd(char **argv)
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

int	__pwd(char **argv)
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

int	__env(char **argv)
{
	extern char **environ;
	int			i;

	(void)argv;
	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);				/* $LINES, $COLUMNS */
	return (0);
}

int	__echo(char **argv)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 0;
	if (argv[1])
	{
		if (!ft_strncmp(argv[1], "-n", ft_strlen(argv[1])))
		{
			flag_n = 1;
			i++;
		}
		while (argv[++i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
		}
	}
	if (!flag_n)
		printf("\n");
	return (0);
}

int __exit(char **argv)
{
	long long	exit_code;
	int			len;

	// if (argc > 2)							/* have to know argc */
	// 	return ();								/* exit: too many arguments */

	exit_code = 0LL;
	if (argv[1])
	{
		exit_code = atonum(argv[1], &len);
		if (exit_code == NON_NUMERIC)			/* exit: string: numeric argument required */
			return (-1);
	}
	return ((int)exit_code);
}

int	__export(char **argv)
{
	(void)argv;
	return (0);
}

int	__unset(char **argv)
{
	(void)argv;
	return (0);
}

int	run_builtin(char **argv)
{
	if (!ft_strncmp(argv[0], "cd", 2))
		return (__cd(argv));
	if (!ft_strncmp(argv[0], "pwd", 3))
		return (__pwd(argv));
	if (!ft_strncmp(argv[0], "env", 3))
		return (__env(argv));
	if (!ft_strncmp(argv[0], "echo", 4))
		return (__echo(argv));
	if (!ft_strncmp(argv[0], "unset", 5))
		return (__unset(argv));
	if (!ft_strncmp(argv[0], "export", 6))
		return (__export(argv));
	return (0);
}

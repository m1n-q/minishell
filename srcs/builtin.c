/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:30:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/14 22:33:48 by mishin           ###   ########.fr       */
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
	int			i;

	(void)argv;
	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);				/* What is $LINES, $COLUMNS */
	return (0);
}

int	__env__(char **argv)
{
	int			i;

	i = -1;
	while (argv[++i])
		printf("%s\n", argv[i]);				/* What is $LINES, $COLUMNS */
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
	// 	return ();								/* exit: too many arguments => it does not exit */
	exit_code = 0LL;
	if (argv[1])
	{
		exit_code = atonum(argv[1], &len);
		if (exit_code == NON_NUMERIC)			/* exit: string: numeric argument required */
		{
			puterr(ENONUM);
			return (-1);
		}
	}
	return ((int)exit_code);
}

char	**environ_to_heap(void)
{
	int		i;
	int		num_env;
	char	**new_environ;

	num_env = get_argc(environ);
	new_environ = (char **)ft_calloc(num_env + 1, sizeof(char *));
	if (!new_environ)
		return (NULL);

	i = -1;
	while (environ[++i])
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
		{
			free_till(i, new_environ);
			free(new_environ);
			return (NULL);
		}
	}
	return (new_environ);
}

int	__export(char **argv)
{
	int		argc;
	int		num_env;
	char	**new_environ;

	argc = get_argc(argv);
	if (argc == 1)
		return (__env(argv));				//NOTE: export: TMP="" / env: TMP=
	/* if (arg w/o '=value') { VAR='' } */
	num_env = get_argc(environ);
	new_environ = (char **)ft_calloc(num_env + 2, sizeof(char *));
	ft_memcpy(new_environ, environ, sizeof(char *) * num_env);
	new_environ[num_env] = "newenviron=inserted";
	free(environ);
	environ = new_environ;

	/* if (arg 'VAR=value') { VAR='value' } */
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

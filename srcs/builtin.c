/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:30:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 18:44:57 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern unsigned char	g_exit_code;
/*
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ env with no options or arguments
◦ echo with option -n
◦ exit with no options
◦ unset with no options
◦ export with no options
*/

/*
	static int
	builtin_status (result)
		int result;
	{
	int r;

	switch (result)
	{
	case EX_USAGE:
		r = EX_BADUSAGE;
		break;
	case EX_REDIRFAIL:
	case EX_BADSYNTAX:
	case EX_BADASSIGN:
	case EX_EXPFAIL:
		r = EXECUTION_FAILURE;
		break;
	default:
		r = EXECUTION_SUCCESS;
		break;
	}
	return (r);
	}
*/

//NOTE: need to handle additional (not supported) args
//NOTE: in bash, echo & pwd could get sh_wrerror (ferror(stdout))
//TODO: builtin error : common / individual
int	is_builtin(char *arg)
{
	if (is_equal(arg, "cd") || \
		is_equal(arg, "pwd") || \
		is_equal(arg, "env") || \
		is_equal(arg, "echo") || \
		is_equal(arg, "exit") || \
		is_equal(arg, "unset") || \
		is_equal(arg, "export"))
		return (1);
	return (0);
}

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

int	__pwd(char **argv)
{
	char	*cwd;
	char	*error_str;

	(void)argv;	//TODO: check opt, print invalid option
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_str = ft_strjoin\
		("pwd: error retrieving current directory: \
		getcwd: cannot access parent directories: ", \
		strerror(errno));			//TODO: error for join
		ft_putstr_fd(error_str, STDERR_FILENO);

		free(error_str);
		return (EXECUTION_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXECUTION_SUCCESS);
}

//TODO: getopt and handle
int	__env(char **argv)
{
	int			i;

	(void)argv;
	i = -1;
	while (environ[++i])
	{
		if (getenv(get_envent(environ[i]).name))
			printf("%s\n", environ[i]);					/* Only 'name' that has '=value' */
	}
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
		if (is_equal(argv[1], "-n"))
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

/*
	if (list && list->word && ISOPTION (list->word->word, '-'))
		list = list->next;
*/
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
			g_exit_code = (unsigned char)-1;
			return (-1);
		}
	}
	g_exit_code = (int)exit_code;
	return ((int)exit_code);
}

//TODO: getopt and handle
int	__export(char **argv)
{
	int		i;
	int		argc;

	argc = get_argc(argv);
	if (argc == 1)
		return (print_including_empty());			/* print including just 'name' */

	i = 0;
	while (argv[++i])
		if (!check_arg(argv[i]))
			g_exit_code = EXECUTION_FAILURE;
	return (0);
}

int	run_builtin(char **argv)
{
	if (is_equal(argv[0], "cd"))
		return (__cd(argv));
	if (is_equal(argv[0], "pwd"))
		return (__pwd(argv));
	if (is_equal(argv[0], "env"))
		return (__env(argv));
	if (is_equal(argv[0], "echo"))
		return (__echo(argv));
	if (is_equal(argv[0], "unset"))
		return (__unset(argv));
	if (is_equal(argv[0], "export"))
		return (__export(argv));
	return (0);
}

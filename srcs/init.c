/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:18:57 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 15:23:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_level(void)
{
	t_envent	shlvl;
	int			level;
	char		*newval;

	shlvl = find_envent("SHLVL");
	if (!shlvl.value)
		add_envent(shlvl.name, "1");
	else
	{
		remove_envent(shlvl);
		level = ft_atoi(shlvl.value);
		newval = itoa_(level + 1);
		add_envent(shlvl.name, newval);
		free(newval);
	}
	free_envent(shlvl);
	return (0);
}

int	static_stream(int mode)
{
	static int	stdin_copied;
	static int	stdout_copied;

	if (mode == DUPLCTE && !stdin_copied && !stdout_copied)
	{
		stdin_copied = dup(STDIN_FILENO);
		stdout_copied = dup(STDOUT_FILENO);
	}
	else if (mode == RESTORE && stdin_copied && stdout_copied)
	{
		restore_stream(stdin_copied, STDIN_FILENO);
		restore_stream(stdout_copied, STDOUT_FILENO);
	}
	else if (mode == STDOUT)
		return (stdout_copied);
	else if (mode == DESTROY && stdin_copied && stdout_copied)
	{
		close(stdin_copied);
		close(stdout_copied);
	}
	else
		return (-1);
	return (0);
}

void	environ_to_heap(void)
{
	int		i;
	int		env_len;
	char	**new_environ;

	env_len = get_argc(environ);
	new_environ = (char **)calloc_(env_len + 1, sizeof(char *));
	i = -1;
	while (environ[++i])
		new_environ[i] = strdup_(environ[i]);
	environ = new_environ;
}

/* add dummy variable $LINES, $COLUMNS to prevent realloc environ by readline */
void	dummy_lc(void)
{
	static int	init;
	static char	*lp;
	static char	*cp;

	if (init == 0)
	{
		lp = add_envent("LINES", "0");
		cp = add_envent("COLUMNS", "0");
		init = -1;
	}
	else if (init == -1)
	{
		free(lp);
		free(cp);
		init = -2;
	}
	else
		return ;
}

void	init_shell(void)
{
	int	error;

	error = init_terminal_data();
	if (error)
	{
		puterr(error);
		exit(-1);
	}
	environ_to_heap();
	shell_level();
	__siglist(SET, 0);
	dummy_lc();
	set_sighandlers();
	static_stream(DUPLCTE);
	settty(SAVE, 0);
	settty(OFF, ECHOCTL);
	get_or_set_interactive(SET, ON);
}

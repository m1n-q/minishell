/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:18:57 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 14:31:36 by mishin           ###   ########.fr       */
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
		newval = ft_itoa(level + 1);
		add_envent(shlvl.name, newval);
		free(shlvl.name);
		free(shlvl.value);
		free(newval);
	}
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
		if (!isatty(STDIN_FILENO))
		{
			close(STDIN_FILENO);
			restore_stream(stdin_copied, STDIN_FILENO);
		}
		if (!isatty(STDOUT_FILENO))
		{
			close(STDOUT_FILENO);
			restore_stream(stdout_copied, STDOUT_FILENO);
		}
	}
	else if (mode == DESTROY && stdin_copied && stdout_copied)
	{
		close(stdin_copied);
		close(stdout_copied);
	}
	else
		return (-1);
	return (0);
}

void	echoctl_off(void)
{
	extern int	_rl_echo_control_chars;

	_rl_echo_control_chars = 0;
}

int	init_shell(void)
{
	int	error;

	environ = environ_to_heap();
	error = init_terminal_data();
	// if (error)
	// 	return (puterr(error));
	set_sighandlers();
	shell_level();
	static_stream(DUPLCTE);
	echoctl_off();
	get_or_set_interactive(SET, ON);
	return (0);
}

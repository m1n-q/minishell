/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:01:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/04 16:25:44 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* eof(-1) print <?> */
void	sig_handler_interactive(int sig)
{
	char	eof;

	if (sig == SIGINT && get_or_set_interactive(GET, 0) == ON)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (get_or_set_interactive(GET, 0) == ON_HD)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		eof = -1;
		ioctl(STDIN_FILENO, TIOCSTI, &eof);
		rl_done = 1;
	}
	return ;
}

void	sigstop_handler(int sig)
{
	if (sig == SIGSTOP)
		signal(SIGCONT, sigcont_handler);
}

void	sigcont_handler(int sig)
{
	if (sig == SIGCONT)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
}

void	set_sighandlers(void)
{
	signal(SIGINT, sig_handler_interactive);
	signal(SIGSTOP, sigstop_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int	get_or_set_interactive(int mode, int val)
{
	static int	interactive;

	if (mode == GET)
		return (interactive);
	else if (mode == SET)
		interactive = val;
	return (interactive);
}

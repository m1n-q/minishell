/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:01:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 01:56:21 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

void	sig_handler_interactive(int sig)
{
	if (sig == SIGINT && get_or_set_interactive(GET, 0) == ON)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
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
		exit_(get_or_set_exitcode(GET, 0));
}

void	sig_jobcontrol(int mode)
{
	if (mode == OFF)
	{
		signal(SIGTSTP, SIG_IGN);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
	else if (mode == ON)
	{
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
	}
}

void	set_sighandlers(void)
{
	signal(SIGINT, sig_handler_interactive);
	signal(SIGSTOP, sigstop_handler);
	sig_jobcontrol(OFF);
	signal(SIGQUIT, SIG_IGN);
}

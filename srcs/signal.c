/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:01:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 23:26:35 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_interactive(int sig)
{
	if (sig == SIGINT && g_interactive)
	{
		printf("\n");
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

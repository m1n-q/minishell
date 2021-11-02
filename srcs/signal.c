/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:01:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 17:59:04 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_interactive;

void	sig_handler_interactive(int sig)
{
	if (sig == SIGINT && g_interactive)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);		// replace rl_line_buffer(line gathered so far) to ""
		rl_redisplay();				// redisplay prompt?
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

int	sigint_event_hook(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);		// replace rl_line_buffer(line gathered so far) to ""
	rl_redisplay();				// redisplay prompt?
	return (0);
}


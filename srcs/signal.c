/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:01:25 by mishin            #+#    #+#             */
/*   Updated: 2021/10/25 18:18:04 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_interactive(int signum)
{
	if (signum == SIGINT)
		return ;
}

int	sigint_event_hook(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);		// replace rl_line_buffer(line gathered so far) to ""
	rl_redisplay();				// redisplay prompt?
	return (0);
}

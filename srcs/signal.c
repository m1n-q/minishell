/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:01:25 by mishin            #+#    #+#             */
/*   Updated: 2021/10/22 22:59:57 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);		// replace rl_line_buffer(line gathered so far) to ""
		printf("\n");
		rl_on_new_line();
		rl_redisplay();				//
	}
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		return ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 22:26:55 by mishin            #+#    #+#             */
/*   Updated: 2021/11/05 22:27:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_or_set_exitcode(int mode, int val)
{
	static int	exitcode;

	if (mode == GET)
		return (exitcode);
	else if (mode == SET)
		exitcode = val;
	return (exitcode);
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

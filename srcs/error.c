/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:47:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/12 16:46:25 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	puterr(int error)
{
	if (error < 0)
	{
		if (error == ENOTERMENV)
			ft_putstr_fd("Specify a termtype with $TERM\n", STDERR_FILENO);
		if (error == ENOTERMENT)
			ft_putstr_fd("No such terminal entry\n", STDERR_FILENO);
		if (error == ENOTERMINFO)
			ft_putstr_fd("Cannot find terminfo database\n", STDERR_FILENO);
		return (error);
	}
	return (errno);
}

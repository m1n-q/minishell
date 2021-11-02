/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:18:57 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 22:39:26 by mishin           ###   ########.fr       */
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

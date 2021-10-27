/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:40:55 by mishin            #+#    #+#             */
/*   Updated: 2021/10/27 14:23:52 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: getopt and handle
int	__env(char **argv)
{
	int			i;

	(void)argv;
	i = -1;
	while (environ[++i])
	{
		if (getenv(find_envent(environ[i]).name))
			printf("%s\n", environ[i]);					/* Only 'name' that has '=value' */
	}
	return (0);
}

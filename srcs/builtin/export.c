/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:24 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:43:16 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: getopt and handle
int	__export(char **argv)
{
	int		i;
	int		argc;

	argc = get_argc(argv);
	if (argc == 1)
		return (print_including_empty());			/* print including just 'name' */

	i = 0;
	while (argv[++i])
		if (!check_arg(argv[i]))
			// g_exit_code = EXECUTION_FAILURE;
			;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:21 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:41:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__echo(char **argv)
{
	int	flag_n;
	int	i;

	flag_n = 0;
	i = 0;
	if (argv[1])
	{
		if (is_equal(argv[1], "-n"))
		{
			flag_n = 1;
			i++;
		}
		while (argv[++i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
		}
	}
	if (!flag_n)
		printf("\n");
	return (0);
}

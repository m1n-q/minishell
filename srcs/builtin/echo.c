/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:21 by mishin            #+#    #+#             */
/*   Updated: 2021/10/28 21:04:16 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__echo(char **argv)
{
	int	nflag;
	int	i;

	nflag = 0;
	i = 0;
	if (argv[1])
	{
		if (isoption(argv[1], TIL_SEC))
		{
			if (argv[1][1] == 'n')
			{
				nflag++;
				i++;
			}
		}
		while (argv[++i])
		{
			printf("%s", argv[i]);
			if (argv[i + 1] != NULL)
				printf(" ");
		}
	}
	if (!nflag)
		printf("\n");
	return (0);
}

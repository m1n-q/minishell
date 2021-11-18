/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:21 by mishin            #+#    #+#             */
/*   Updated: 2021/11/19 02:35:12 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__echo(t_cmd cmd)
{
	int	nflag;
	int	i;

	nflag = 0;
	i = skip_empty_vars(cmd, 0);
	if (cmd.argv[i])
	{
		if (isoption(cmd.argv[i], TIL_SEC) && cmd.argv[i][1] == 'n')
		{
			nflag++;
			i++;
		}
		while (i < cmd.argc)
		{
			if (cmd.argv[i])
				printf("%s", cmd.argv[i]);
			if (cmd.argv[i] && cmd.argv[skip_empty_vars(cmd, i)])
				printf(" ");
			i = skip_empty_vars(cmd, i);
		}
	}
	if (!nflag)
		printf("\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:44:21 by mishin            #+#    #+#             */
/*   Updated: 2021/11/17 20:42:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_till(int index, char **arr)
{
	int	i;

	i = -1;
	while (++i < index)
	{
		if (arr[i] != EMPTY_VAR && is_token(arr[i]) == 0)
			free(arr[i]);
	}
}

void	free_cmd_table(t_cmd *cmd_table, int len_cmd_table)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len_cmd_table)
	{
		j = -1;
		while (++j < cmd_table[i].argc)
		{
			if (is_token(cmd_table[i].argv[j]) == 0 \
			&& cmd_table[i].argv[j] != EMPTY_VAR)
				free(cmd_table[i].argv[j]);
		}
		free(cmd_table[i].argv);
		if (cmd_table[i].path != NOCMD)
			free(cmd_table[i].path);
	}
	free(cmd_table);
}

void	free_envent(t_envent entry)
{
	free(entry.name);
	free(entry.value);
}

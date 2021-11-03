/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:19:31 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 15:12:18 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_cmd_table(t_cmd *cmd_table, int len_cmd_table)
{
	int	i;

	i = -1;
	while (++i < len_cmd_table)
	{
		if (check_redir(&cmd_table[i]) == -1)
			cmd_table[i].any_err = 1;
		trim_redir(&(cmd_table[i].argv), count_redir(&cmd_table[i]));
		set_path(&cmd_table[i]);
		if (i < len_cmd_table - 1)
		{
			make_pipe(&cmd_table[i]);
			set_pipe_stream(&cmd_table[i], &(cmd_table[i + 1]));
		}
	}
	return (0);
}

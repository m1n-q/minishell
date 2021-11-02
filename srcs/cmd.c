/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:19:31 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 16:28:51 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	check_cmd_table(t_cmd *cmd_table, int len_cmd_table)
{
	int	i;
	int	count_redir;

	i = -1;
	while (++i < len_cmd_table)
	{
		check_redir(&cmd_table[i], &count_redir);
		trim_redir(&(cmd_table[i].argv), count_redir);
		set_path(&cmd_table[i]);
		if (i < len_cmd_table - 1) // except last cmd
		{
			make_pipe(&cmd_table[i]);
			set_pipe_stream(&cmd_table[i], &(cmd_table[i + 1]));
		}
	}
	return (0);
}

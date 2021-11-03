/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:55:36 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 17:51:04 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	connect_stream(t_io_table stream)
{
	if (stream.in != DEFAULT)
	{
		dup2(stream.in, STDIN_FILENO);
		close(stream.in);
	}
	if (stream.out != DEFAULT)
	{
		dup2(stream.out, STDOUT_FILENO);
		close(stream.out);
	}
	return (0);
}

int	destroy_stream(t_io_table stream)
{
	if (stream.out != DEFAULT)
		close(stream.out);
	if (stream.in != DEFAULT)
		close(stream.in);
	return (0);
}

int	restore_stream(int std_copied, int std_org)
{
	if (!isatty(std_org))
	{
		close(std_org);
		dup2(std_copied, std_org);
	}
	return (0);
}

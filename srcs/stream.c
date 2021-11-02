/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:55:36 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 16:42:37 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	connect_stream(t_io_table stream)
{
	if (stream.in != -1)
	{
		dup2(stream.in, STDIN_FILENO);
		close(stream.in);
	}
	if (stream.out != -1)
	{
		dup2(stream.out, STDOUT_FILENO);
		close(stream.out);
	}
	return (0);
}

int	destroy_stream(t_io_table stream)
{
	if (stream.out != -1)
		close(stream.out);
	if (stream.in != -1)
		close(stream.in);
	return (0);
}

/* 1) copy std -> restore to (0, 1) -> close(copied) */
/* 2) copy std and keep them stored till program ends */
int	restore_stream(int std_copied, int std_org)
{
	dup2(std_copied, std_org);
	// close(std_copied);
	return (0);
}

/*
	new1 == new1
	1 == stdout
	...	1 = new1;
	... return ( org_stdout );

	new3 == new3
	1 == new1
	...	1 = new3;
	... return (new1);
*/

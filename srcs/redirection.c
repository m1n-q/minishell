/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:40:16 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/18 19:49:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

//NOTE: '>' 을 기준으로 쪼개서 run 해야 할 듯..

int	redirect_in(char *arg)
{
	int	fd;
	int std_copied;

	std_copied = dup(STDIN_FILENO);
	fd = open(arg, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (std_copied);
}

int	redirect_out(char *arg)
{
	int	fd;
	int	std_copied;

	/* if AMP && instream */
	// redirect instream to . . .

	/* if AMP && outstream */
	// redirect to outstream, not to arg

	/* else */
	std_copied = dup(STDOUT_FILENO);
	fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (std_copied);
}

int	redirect_append(char *arg)
{
	int	fd;
	int	std_copied;

	/* if AMP && instream */
	// redirect instream to . . .

	/* if AMP && outstream */
	// Not redirect to outstream, >>&1 : append to filename '1'

	/* else */
	std_copied = dup(STDOUT_FILENO);
	fd = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (std_copied);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:40:16 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/13 17:13:20 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

void	read_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		printf("minishell: no such file or directory: %s\n", filename);
	if (dup2(fd, 0) == -1)
		printf("dup2 failed\n");
	close(fd);
}

void	write_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (dup2(fd, 1) == -1)
		printf("dup2 failed\n");
	close(fd);
}

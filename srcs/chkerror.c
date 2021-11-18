/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chkerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:27:03 by mishin            #+#    #+#             */
/*   Updated: 2021/11/19 02:35:53 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_sample(char *file, char *buf)
{
	int	fd;
	int	len;

	fd = open(file, O_RDONLY);
	if (fd >= 0)
	{
		len = read(fd, buf, 80);
		close(fd);
	}
	else
		len = -1;
	return (len);
}

int	check_binary_file(char *sample, int sample_len)
{
	register int	i;
	unsigned char	c;

	i = -1;
	while (++i < sample_len)
	{
		c = sample[i];
		if (c == '\n')
			return (0);
		if (c == '\0')
			return (1);
	}
	return (0);
}

int	check_sample(char *command)
{
	int			sample_len;
	char		sample[80];

	sample_len = read_sample(command, sample);
	if (sample_len == 0)
		return (0);
	else if (sample_len < 0)
	{
		file_error(command);
		return (EX_NOEXEC);
	}
	else
	{
		if (check_binary_file(sample, sample_len))
		{
			internal_error(command, "cannot execute binary file");
			return (EX_BINARY_FILE);
		}
	}
	return (-1);
}

/* e : save error from execve(), prevent overwrite from stat() */
int	check_error(char *command)
{
	struct stat	finfo;
	int			e;

	e = errno;
	if (e != ENOEXEC)
	{
		if ((stat(command, &finfo) == 0) && (S_ISDIR(finfo.st_mode)))
			internal_error(command, "is a directory");
		else
		{
			errno = e;
			file_error(command);
		}
		if (e == ENOENT)
			return (EX_NOTFOUND);
		else
			return (EX_NOEXEC);
	}
	return (check_sample(command));
}

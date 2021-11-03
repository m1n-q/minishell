/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:47:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 14:34:59 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	get_or_set_exitcode(int mode, int val)
{
	static int	exitcode;

	if (mode == GET)
		return (exitcode);
	else if (mode == SET)
		exitcode = val;
	return (exitcode);
}

int	puterr(int error)
{
	if (error < 0)
	{
		if (error == ENOTERMENV)
			ft_putstr_fd("specify a termtype with $TERM", STDERR_FILENO);
		if (error == ENOTERMENT)
			ft_putstr_fd("no such terminal entry", STDERR_FILENO);
		if (error == ENOTERMINFO)
			ft_putstr_fd("cannot find terminfo database", STDERR_FILENO);
		if (error == ENONUM)
			ft_putstr_fd("numeric argument required", STDERR_FILENO);
		if (error == E2MANY)
			ft_putstr_fd("too many arguments", STDERR_FILENO);
	}
	else
		ft_putstr_fd(strerror(error), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (error);
}

void	internal_error(char *command, char *err_string)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_string, ft_strlen(err_string));
	write(STDERR_FILENO, "\n", 1);
}

void	file_error(char *command)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
}

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

int	check_error(char *command)
{
	struct stat	finfo;
	int			e;
	int			sample_len;
	char		sample[80];

	e = errno; /* error from execve() */
	if (e != ENOEXEC)
	{
		if ((stat(command, &finfo) == 0) && (S_ISDIR(finfo.st_mode)))
			internal_error(command, "is a directory");
		else
		{
			errno = e;
			file_error(command);
		}
		return ((e == ENOENT) ? EX_NOTFOUND : EX_NOEXEC);
	}
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
	return (-1); /*NOTREACHED*/
}

char	**syntax_error(char **error, int exit_code)
{
	g_exit_code = exit_code;
	write(STDERR_FILENO, "minishell: ", 11);
	if (error == (char **)Q_ERR)
		write(STDERR_FILENO, "quotes do not match\n", 20);
	else if (error == (char **)PIPE_ERR || error == (char **)REDIR_ERR)
	{
		write(STDERR_FILENO, "syntax error near unexpected token ", 35);
		if (error == (char **)PIPE_ERR)
			write(STDERR_FILENO, "`|'\n", 4);
		else
			write(STDERR_FILENO, "`newline'\n", 10);
	}
	else if (error == (char **)UNEXPECTED_EOF)
		write(STDERR_FILENO, "syntax error: unexpected end of file\n", 37);
	return (error);
}

//  if (fd < 0)
//     {
//       e = errno;
//       file_error (filename);
//       exit ((e == ENOENT) ? EX_NOTFOUND : EX_NOINPUT);
//     }

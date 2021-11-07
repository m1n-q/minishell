/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:47:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/07 22:59:52 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**syntax_error(char **error, char *token, int exit_code)
{
	get_or_set_exitcode(SET, exit_code);
	ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
	if (error == (char **)Q_ERR)
		ft_putendl_fd(": quote unclosed", STDERR_FILENO);
	else if (error == (char **)UNEXPECTED_EOF)
		ft_putendl_fd(": unexpected end of file", STDERR_FILENO);
	else if (error == (char **)PIPE_ERR || error == (char **)REDIR_ERR)
	{
		ft_putstr_fd(" near unexpected token ", STDERR_FILENO);
		ft_putendl_fd(token, STDERR_FILENO);
	}
	else if (error == (char **)INVALID_REDIR)
	{
		ft_putstr_fd(": invalid token: ", STDERR_FILENO);
		ft_putendl_fd(token, STDERR_FILENO);
	}
	return (error);
}

int	builtin_error(char *command, char *arg, char *message, int optflag)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (command && *command)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": ", 2);
	}
	if (arg && *arg && !optflag)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	if (arg && *arg && optflag)
	{
		write(STDERR_FILENO, arg, 2);
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (0);
}

//  if (fd < 0)
//     {
//       e = errno;
//       file_error (filename);
//       exit ((e == ENOENT) ? EX_NOTFOUND : EX_NOINPUT);
//     }

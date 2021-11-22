/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:47:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/22 23:52:56 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

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
	ft_putendl_fd("", STDERR_FILENO);
	return (error);
}

void	internal_error(char *command, char *err_string)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(err_string, STDERR_FILENO);
}

void	file_error(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

char	**syntax_error(char **error, char *token, int exit_code)
{
	get_or_set_exitcode(SET, exit_code);
	ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
	if (error == Q_ERR)
	{
		ft_putendl_fd(": quote unclosed", STDERR_FILENO);
		return (error);
	}
	else if (error == UNEXPECTED_EOF)
		ft_putendl_fd(": unexpected end of file", STDERR_FILENO);
	else if (error == PIPE_ERR || error == REDIR_ERR)
	{
		ft_putstr_fd(" near unexpected token ", STDERR_FILENO);
		ft_putendl_fd(token, STDERR_FILENO);
	}
	else if (error == INVALID_REDIR)
	{
		ft_putstr_fd(": invalid token: ", STDERR_FILENO);
		ft_putendl_fd(token, STDERR_FILENO);
	}
	return (error);
}

int	builtin_error(char *command, char *arg, char *message, int optflag)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command && *command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg && *arg && !optflag)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg && *arg && optflag)
	{
		write(STDERR_FILENO, arg, 2);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:50:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/28 21:02:39 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_coloned_str(char *a, char *b)
{
	char	*tmp;
	char	*coloned_str;

	tmp = ft_strjoin(a, ": ");
	if (!tmp)
		return (NULL);
	coloned_str = ft_strjoin(tmp, b);
	free(tmp);
	if (!coloned_str)
		return (NULL);
	return (coloned_str);
}

char	*get_quoted_str(char *s)
{
	char	*tmp;
	char	*quoted_str;

	tmp = ft_strjoin("`", s);
	if (!tmp)
		return (NULL);
	quoted_str = ft_strjoin(tmp, "'");
	free(tmp);
	if (!quoted_str)
		return (NULL);
	return (quoted_str);
}

int	builtin_error(char *command, char *arg, char *message, int optflag)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
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

void	sh_invalidopt(char *command, char *opt)
{
	builtin_error(command, opt, "invalid option", 1);
}

void	sh_invalidid (char *command, char *s)
{
	char	*qs;

	qs = get_quoted_str(s);
	if (!qs)
		return ;
	builtin_error(command, qs, "not a valid identifier", 0);
	free(qs);
}

void	sh_neednumarg (char *command, char *s)
{
	builtin_error (command, s, "numeric argument required", 0);
}

void	builtin_usage (char *command, char *usage)
{
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "usage: ", 7);
	write(STDERR_FILENO, usage, ft_strlen(usage));
	write(STDERR_FILENO, "\n", 1);
}

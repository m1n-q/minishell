/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:50:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 17:58:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_coloned_str(char *a, char *b)
{
	char *tmp;
	char *coloned_str;

	tmp = ft_strjoin(a, ": ");
	if (!tmp)
		return (NULL);
	coloned_str = ft_strjoin(tmp, b);
	free(tmp);
	if (!coloned_str)
		return (NULL);
	return (coloned_str);
}

int	builtin_error(char *command, char *arg, char *message)
{
  	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	if (arg && *arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (0);
}

void	sh_invalidopt(char *command, char *opt)
{
	// char *error_str;

	// error_str = get_coloned_str(command, opt);
	// if (!error_str)
	// 	return ;

	builtin_error (command, opt, "invalid option");
	// free(error_str);
}

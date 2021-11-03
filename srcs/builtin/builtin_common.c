/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_common.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:50:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 22:10:47 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sh_double_quote(char *string)
{
	int		i;
	char	*ret;

	if (!string)
		return (NULL);
	ret = (char *)ft_calloc(ft_strlen(string) + 3, sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = '"';
	i = -1;
	while (string[++i])
		ret[i + 1] = string[i];
	ret[i + 1] = '"';
	return (ret);
}

void	sh_invalidopt(char *command, char *opt)
{
	builtin_error(command, opt, "invalid option", 1);
}

void	sh_invalidid(char *command, char *s)
{
	char	*qs;

	qs = joinjoin("`", s, "'");
	if (!qs)
		return ;
	builtin_error(command, qs, "not a valid identifier", 0);
	free(qs);
}

void	sh_neednumarg(char *command, char *s)
{
	builtin_error (command, s, "numeric argument required", 0);
}

void	builtin_usage(char *command, char *usage)
{
	write(STDERR_FILENO, command, ft_strlen(command));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "usage: ", 7);
	write(STDERR_FILENO, usage, ft_strlen(usage));
	write(STDERR_FILENO, "\n", 1);
}

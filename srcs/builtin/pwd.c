/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:40:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/18 15:23:58 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__pwd(t_cmd cmd)
{
	char	*cwd;
	char	*error_str;
	int		i;

	i = skip_empty_vars(cmd, 0);
	if (cmd.argv[i])
	{
		if (isoption(cmd.argv[i], TIL_END))
		{
			sh_invalidopt(cmd.argv[0], cmd.argv[i]);
			builtin_usage(cmd.argv[0], PWD_SHORTDOC);
			return (EXECUTION_FAILURE);
		}
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_str = strjoin_("pwd: error retrieving current directory: \
		getcwd: cannot access parent directories: ", strerror(errno));
		ft_putstr_fd(error_str, STDERR_FILENO);
		free(error_str);
		return (EXECUTION_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXECUTION_SUCCESS);
}

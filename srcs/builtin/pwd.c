/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:40:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 17:18:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: error for join
int	__pwd(char **argv)
{
	char	*cwd;
	char	*error_str;

	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);
			return (EXECUTION_FAILURE);
		}
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_str = ft_strjoin \
		("pwd: error retrieving current directory: \
		getcwd: cannot access parent directories: ", \
		strerror(errno));
		ft_putstr_fd(error_str, STDERR_FILENO);
		free(error_str);
		return (EXECUTION_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXECUTION_SUCCESS);
}

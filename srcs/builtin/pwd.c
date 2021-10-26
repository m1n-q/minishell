/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:40:25 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:40:38 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__pwd(char **argv)
{
	char	*cwd;
	char	*error_str;

	(void)argv;	//TODO: check opt, print invalid option
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_str = ft_strjoin\
		("pwd: error retrieving current directory: \
		getcwd: cannot access parent directories: ", \
		strerror(errno));			//TODO: error for join
		ft_putstr_fd(error_str, STDERR_FILENO);

		free(error_str);
		return (EXECUTION_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXECUTION_SUCCESS);
}

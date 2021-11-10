/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:27:08 by mishin            #+#    #+#             */
/*   Updated: 2021/11/10 16:22:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_tmp_environ(void)
{
	char	**tmp_environ;
	int		i;

	tmp_environ = (char **)calloc_(get_argc(environ) + 1, sizeof(char *));
	i = -1;
	while (environ[++i])
		tmp_environ[i] = strdup_(environ[i]);
	return (tmp_environ);
}

char	*get_env_including_empty(char *arg)
{
	int		i;
	char	*env_val;
	char	*env_string;

	env_val = getenv(arg);
	if (env_val)
	{
		env_string = joinjoin(arg, "=", env_val);
		i = -1;
		while (environ[++i])
		{
			if (is_equal(environ[i], env_string))
			{
				free(env_string);
				return (environ[i]);
			}
		}
		free(env_string);
	}
	i = -1;
	while (environ[++i])
		if (is_equal(environ[i], arg))
			return (environ[i]);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:47:17 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 00:05:15 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envent	find_envent(char *name)
{
	t_envent	env;
	int			assign_pos;
	int			i;

	env.index = -1;
	env.string = NULL;
	env.value = NULL;
	env.name = strdup_(name);
	env.string = get_env_including_empty(env.name);
	if (env.string)
	{
		i = -1;
		while (environ[++i] && env.index == -1)
			if (is_equal(environ[i], env.string))
				env.index = i;
		assign_pos = get_assign_pos(env.string);
		if (assign_pos)
			env.value = strdup_(env.string + assign_pos + 1);
	}
	return (env);
}

char	*add_envent(char *name, char *value)
{
	int		env_len;
	char	**new_environ;
	char	*env_string;

	env_string = NULL;
	env_len = get_argc(environ);
	new_environ = (char **)calloc_(env_len + 2, sizeof(char *));
	ft_memmove(new_environ, environ, sizeof(char *) * env_len);
	if (value)
		env_string = joinjoin(name, "=", value);
	else
		env_string = strdup_(name);
	new_environ[env_len] = env_string;
	free(environ);
	environ = new_environ;
	return (env_string);
}

int	remove_envent(t_envent env)
{
	int			env_len;
	char		**new_environ;

	if (env.string)
	{
		env_len = get_argc(environ);
		free(environ[env.index]);
		ft_memmove(environ + env.index, environ + env.index + 1, \
				sizeof(char *) * (env_len - env.index));
		new_environ = (char **)calloc_(env_len, sizeof(char *));
		ft_memmove(new_environ, environ, sizeof(char *) * env_len);
		free(environ);
		environ = new_environ;
	}
	return (0);
}

void	adjust_envent(t_envent entry, char *value)
{
	remove_envent(entry);
	add_envent(entry.name, value);
}

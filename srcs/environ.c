/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:27:08 by mishin            #+#    #+#             */
/*   Updated: 2021/11/09 18:09:15 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_tmp_environ(void)
{
	char	**tmp_environ;
	int		i;

	tmp_environ = (char **)ft_calloc(get_argc(environ) + 1, sizeof(char *));
	if (!tmp_environ)
		return (NULL);
	i = -1;
	while (environ[++i])
		tmp_environ[i] = ft_strdup(environ[i]);
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

//NOTE: env.string will be filled if env.name already exists
t_envent	find_envent(char *name)
{
	t_envent	env;
	int			assign_pos;
	int			i;

	env.index = -1;
	env.string = NULL;
	env.value = NULL;
	env.name = ft_strdup(name);
	env.string = get_env_including_empty(env.name);
	if (env.string)
	{
		i = -1;
		while (environ[++i] && env.index == -1)
			if (is_equal(environ[i], env.string))
				env.index = i;
		assign_pos = get_assign_pos(env.string);
		if (assign_pos)
			env.value = ft_strdup(env.string + assign_pos + 1);
	}
	return (env);
}

int	add_envent(char *name, char *value)
{
	int		env_len;
	char	**new_environ;
	char	*env_string;

	env_string = NULL;
	env_len = get_argc(environ);
	new_environ = (char **)ft_calloc(env_len + 2, sizeof(char *));
	ft_memmove(new_environ, environ, sizeof(char *) * env_len);
	if (value)
		env_string = joinjoin(name, "=", value);
	else
		env_string = ft_strdup(name);
	new_environ[env_len] = env_string;
	free(environ);
	environ = new_environ;
	return (0);
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
		new_environ = (char **)ft_calloc(env_len, sizeof(char *));
		ft_memmove(new_environ, environ, sizeof(char *) * env_len);
		free(environ);
		environ = new_environ;
	}
	return (0);
}

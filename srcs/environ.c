/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:27:08 by mishin            #+#    #+#             */
/*   Updated: 2021/10/27 18:55:37 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**environ_to_heap(void)
{
	int		i;
	int		env_len;
	char	**new_environ;

	env_len = get_argc(environ);
	new_environ = (char **)ft_calloc(env_len + 1, sizeof(char *));
	if (!new_environ)
		return (NULL);

	i = -1;
	while (environ[++i])
	{
		new_environ[i] = ft_strdup(environ[i]);
		if (!new_environ[i])
		{
			free_till(i, new_environ);
			free(new_environ);
			return (NULL);
		}
	}
	return (new_environ);
}

char	*get_env_including_empty(char *arg)
{
	int		i;
	char	*env_val;
	char	*env_string;
	char	*tmp;

	env_val = getenv(arg);
	if (env_val)
	{
		tmp = ft_strjoin(arg, "=");
		env_string = ft_strjoin(tmp, env_val);
		free(tmp);
		i = -1;
		while (environ[++i])
		{
			if (is_equal(environ[i], env_string))
			{
				free(env_string);
				return (environ[i]);
			}
		}
	}
	i = -1;						// searching env without value
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
	char	*tmp;

	env_string = NULL;
	env_len = get_argc(environ);
	new_environ = (char **)ft_calloc(env_len + 2, sizeof(char *));
	ft_memmove(new_environ, environ, sizeof(char *) * env_len);
	if (value)
	{
		tmp = ft_strjoin(name, "=");
		env_string = ft_strjoin(tmp, value);
		free(tmp);
	}
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
		/* remove environ[index] */
		free(environ[env.index]);
		/* move left */
		ft_memmove(environ + env.index, environ + env.index + 1, sizeof(char *) * (env_len - env.index));
		/* resize */
		new_environ = ft_calloc(env_len, sizeof(char *));
		ft_memmove(new_environ, environ, sizeof(char *) * env_len);
		free(environ);
		environ = new_environ;
	}
	return (0);
}

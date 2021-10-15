/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:27:08 by mishin            #+#    #+#             */
/*   Updated: 2021/10/15 21:14:36 by mishin           ###   ########.fr       */
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
		return (env_string);
	}
	i = -1;						// searching env without value
	while (environ[++i])
		if (ft_strlen(environ[i]) == ft_strlen(arg) && \
			!ft_strncmp(environ[i], arg, ft_strlen(arg)))
				return (arg);
	return (NULL);
}

//NOTE: env.string will be filled if env.name already exists
t_envent	get_envent(char *arg)
{
	char		*pos;
	t_envent	env;
	int			i;

	env.index = -1;
	env.string = NULL;
	pos = ft_strchr(arg, '=');
	if (pos)							/* export 'arg=val' */
	{
		env.name = ft_substr(arg, 0, (size_t)(pos - arg));		//FIXIT: free
		env.string = get_env_including_empty(env.name);
	}
	else								/* export 'arg' */
	{
		env.name = arg;
		env.string = get_env_including_empty(arg);
	}
	if (env.string)
	{
		i = -1;
		while (environ[++i] && env.index == -1)
			if (ft_strlen(environ[i]) == ft_strlen(env.string) && \
				!ft_strncmp(environ[i], env.string, ft_strlen(env.string)))
				env.index = i;
	}
	return (env);
}

int	append_envent(char *arg)		//FIXIT: naming: do not use "envent"
{
	int		env_len;
	char	**new_environ;

	env_len = get_argc(environ);
	new_environ = (char **)ft_calloc(env_len + 2, sizeof(char *));
	ft_memmove(new_environ, environ, sizeof(char *) * env_len);
	new_environ[env_len] = ft_strdup(arg);
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

int	check_arg(char *arg)
{
	char		*pos;
	t_envent	env;

	env = get_envent(arg);
	pos = ft_strchr(arg, '=');
	if (env.string)
	{
		if (pos)		/* if exists && str=='name=value' : modify existing entry */
		{
			remove_envent(env);
			append_envent(arg);
		}
		else			/* if exists && str=='name' : ignore */
			return (0);
	}
	else
	{
		if (pos)		/* if new && str=='name=value' : append new entry */
			append_envent(arg);
		else			/* if new && str=='name' : append new entry */
			append_envent(arg);
	}
	//NOTE:: export print just 'arg', env(getenv) cannot know
	return (0);
}

int	print_including_empty(void)
{
	int			i;

	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);				/* Only 'NAME'='VAL' */
	return (0);
}

int	__unset(char **argv)
{
	t_envent	env;
	int			i;

	if (!argv || !*argv)
		return (-1);
	i = 0;
	while (argv[++i])
	{
		env = get_envent(argv[i]);
		remove_envent(env);
	}
	return (0);
}

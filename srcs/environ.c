/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:27:08 by mishin            #+#    #+#             */
/*   Updated: 2021/10/15 16:55:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**environ_to_heap(void)
{
	int		i;
	int		num_env;
	char	**new_environ;

	num_env = get_argc(environ);
	new_environ = (char **)ft_calloc(num_env + 1, sizeof(char *));
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

char	**check_arg(char *arg)
{
	char	*pos;
	char	*name;
	char	*val;

	pos = ft_strchr(arg, '=');
	if (pos)
	{
		name = ft_substr(arg, 0, (size_t)(pos - arg));
		val = getenv(name);

		if (val)					/* if exists : modify existing entry */
			;
		else						/* else : append new entry */
		;

									// case: var= || var='' , it exported with '' value
	}
	else							/* export arg */
	{
		name = arg;
		val = getenv(name);

		if (val)					/* if exists : ignore command */
			return (NULL);
		else 						/* else : append new entry 'arg' */

									// { export print just 'arg', env cannot know  }
		;
	}
	return (NULL);
}

int	extend_envp(void)
{
	int		num_env;
	char	**new_environ;

	num_env = get_argc(environ);
	new_environ = (char **)ft_calloc(num_env + 2, sizeof(char *));
	ft_memmove(new_environ, environ, sizeof(char *) * num_env);
	new_environ[num_env] = ft_strdup("newenviron=inserted");
	free(environ);	//NOTE: need to free all elems ? maybe it can be reused ..
	environ = new_environ;

	return (0);
}

t_envent	get_envent(char *arg)
{
	char		*pos;
	char		*tmp;
	t_envent	env;
	int			i;

	env.string = NULL;
	env.index = 0;
	pos = ft_strchr(arg, '=');
	if (pos)
		env.name = ft_substr(arg, 0, (size_t)(pos - arg));
	else								/* export arg */
		env.name = arg;
	env.val = getenv(env.name);
	if (env.val)
	{
		tmp = ft_strjoin(env.name, "=");
		env.string = ft_strjoin(tmp, env.val);
		free(tmp);
		i = -1;
		while (environ[++i] && !env.index)
			if (ft_strlen(environ[i]) == ft_strlen(env.string) && \
				!ft_strncmp(environ[i], env.string, ft_strlen(env.string)))
				env.index = i;
	}
	return (env);
	/*
		1. if arg=val && exist	-> name = arg, val = existing
		2. if arg=val && new	-> name = arg, val = existing
		3. if arg && exist		-> name = arg, val = NULL;
		4. if arg && new		-> name = arg, val = NULL;
	*/
}

int	__unset(char **argv)
{
	t_envent	env;
	int			env_len;
	char		**new_environ;

	env = get_envent(argv[1]);
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

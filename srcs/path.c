/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:10:16 by mishin            #+#    #+#             */
/*   Updated: 2021/10/22 19:48:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int has_slash(char *arg)
{
	if (ft_strchr(arg, '/'))
		return (1);
	return (0);
}

char	**get_paths(void)
{
	char	**paths;
	char	*env;

	env = getenv("PATH");
	paths = ft_split(env, ':');
	return (paths);
}

char *find_path(char *arg)
{
	int				i;
	DIR				*dirp;
	char			*path;
	char			**paths;
	struct dirent	*dirent;

	paths = get_paths();
	path = NULL;
	i = -1;
	while (paths[++i])
	{
		dirp = opendir(paths[i]);
		if (dirp)
		{
			while ((dirent = readdir(dirp)))
				if (is_equal(dirent->d_name, arg))
					path = ft_strjoin(ft_strjoin(paths[i], "/"), arg);
			closedir(dirp);
		}
		if (path)
			break ;
	}
	free(paths);
	return (path);
}

int	set_path(t_cmd *cmd)
{
	if (has_slash(cmd->argv[0]))
		cmd->path = cmd->argv[0];
	else
	{
		if (is_builtin(cmd->argv[0]))				//NOTE:it includes __exit case
			cmd->path = "built-in";					//FIXME: "built-in" can be input
		else
			cmd->path = find_path(cmd->argv[0]);	//NOTE:it includes ENOCMD case
	}

	return (0);
}

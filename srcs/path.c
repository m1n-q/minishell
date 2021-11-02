/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 19:10:16 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 20:23:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_slash(char *arg)
{
	if (ft_strchr(arg, '/'))
		return (1);
	return (0);
}

static char	**get_paths(void)
{
	char	**paths;
	char	*env;

	env = getenv("PATH");
	paths = ft_split(env, ':');
	return (paths);
}

static char	*search(char *pathdir, char *arg)
{
	char			*path;
	char			*tmp;
	DIR				*dirp;
	struct dirent	*dirent;

	path = NULL;
	dirp = opendir(pathdir);
	if (dirp)
	{
		dirent = readdir(dirp);
		while (dirent)
		{
			if (is_equal(dirent->d_name, arg))
			{
				tmp = ft_strjoin(pathdir, "/");
				path = ft_strjoin(tmp, arg);
				free(tmp);
				break ;
			}
			dirent = readdir(dirp);
		}
		closedir(dirp);
	}
	return (path);
}

static char	*find_path(char *arg)
{
	int				i;
	char			*path;
	char			**paths;

	paths = get_paths();
	if (!paths)
		return (NULL);
	path = NULL;
	i = -1;
	while (paths[++i])
	{
		path = search(paths[i], arg);
		if (path)
			break ;
	}
	free(paths);
	return (path);
}

int	set_path(t_cmd *cmd)
{
	if (cmd->argv[0] == NULL)
		cmd->path = (char *)NOCMD;
	else if (has_slash(cmd->argv[0]))
		cmd->path = cmd->argv[0];
	else
	{
		if (is_builtin(cmd->argv[0]))
			cmd->path = "built-in";					//FIXME: "built-in" can be input
		else
			cmd->path = find_path(cmd->argv[0]);
	}
	return (0);
}

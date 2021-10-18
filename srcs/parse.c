/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:50:18 by mishin            #+#    #+#             */
/*   Updated: 2021/10/18 20:27:18 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 * initializing flags for qoutes and redirections
 */
void	init_q_r(t_cmd *cmd)
{
	cmd->d_q = 0;
	cmd->s_q = 0;
	cmd->r_in = 0;
	cmd->r_out = 0;
	cmd->here_doc = 0;
	cmd->r_out_a = 0;
}

char	**getpaths(void)
{
	char	**paths;
	char	*env;

	env = getenv("PATH");
	paths = ft_split(env, ':');
	return (paths);
}

char	**getargv(char *input)
{
	char	**argv;

	argv = ft_split_space(input);
	return (argv);
}

t_cmd	parse(char *input)
{
	char			**paths;
	t_cmd			cmd;
	DIR				*dirp;
	struct dirent	*dirent;
	int				i;

	paths = getpaths();
	cmd.argv = getargv(input);
	int	j = -1;
	while (cmd.argv[++j])
	{
		if (cmd.argv[j] > (char *)10LL)
			printf("argv[%d] : %s\n", j, cmd.argv[j]);
		else
			printf("argv[%d] : 🌈\n", j);
	}
	printf("====================================\n");
	cmd.path = NULL;
	if (is_builtin(cmd.argv[0]))
		return (cmd);
	paths = getpaths();
	i = -1;
	while (paths[++i])
	{
		dirp = opendir(paths[i]);
		if (dirp)
		{
			while ((dirent = readdir(dirp)))
				if (dirent->d_namlen == ft_strlen(cmd.argv[0]))
					if (!ft_strncmp(cmd.argv[0], dirent->d_name, dirent->d_namlen))
						cmd.path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd.argv[0]);
			closedir(dirp);
		}
		if (cmd.path)
			break ;
	}
	free(paths);
	return (cmd);
}

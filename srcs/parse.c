/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:50:18 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 19:32:45 by kyumlee          ###   ########.fr       */
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

char	**getargv(char *input, t_cmd *cmd)
{
	char	**argv;

	argv = ft_split_space(input, cmd);
//	argv = ft_split(input, ' ');
	return (argv);
}

t_cmd	parse(char *input)
{
	char			**paths;
	t_cmd			cmd;
	DIR				*dirp;
	struct dirent	*dirent;
	int				i;

	init_q_r(&cmd);

	cmd.argv = getargv(input, &cmd);

	/* print all arguments */
	int	j = 0;
	while (cmd.argv[j])
	{
		printf("argv[%d] : %s\n", j, cmd.argv[j]);
		j++;
	}

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

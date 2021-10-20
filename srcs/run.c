/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:01:59 by mishin            #+#    #+#             */
/*   Updated: 2021/10/21 00:58:48 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//NOTE: '>' 을 기준으로 쪼개서 run 해야 할 듯..
// int	split(t_cmd cmd);
// {
// 	if (PIPE || REDIRECT_IN || REDIRECT_OUT || REDIRECT_APPEND || HEREDOC)
// 	{
// 		if (PIPE)
// 			run argv till PIPE and pipe()
// 		else if (REDIRECT_OUT || REDIRECT_APPEND)
// 			run argv till REDIRECT_OUT and redirect_out(after REDIRECT_OUT)
// 		else if (REDIRECT_IN)
// 			redirect_in(after REDIRECT_IN) and run argv till REDIRECT_IN
// 	}
// 	restore_stream();
// }

int	check_redirection(t_cmd cmd)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (cmd.argv[++i])
	{
		if (cmd.argv[i] == (char *)REDIRECT_OUT || \
			cmd.argv[i] == (char *)REDIRECT_IN)
		{
			count++;
			if (cmd.argv[i + 1])
			{
				if (cmd.argv[i] == (char *)REDIRECT_OUT)
					// redirect_out(argv[i + 1]);
					cmd.io_table.stdout_fd = redirect_out(cmd.argv[i + 1]);

				else if (cmd.argv[i] == (char *)REDIRECT_IN)		//NOTE: what if i == 0 and redirect_in
					// redirect_in(argv[i + 1]);
					cmd.io_table.stdin_fd = redirect_in(cmd.argv[i + 1]);
			}
		}
	}
	return (count);
}

int	get_argv_without_redirection(int count_redirection, char ***argv)
{
	char	**new_argv;
	int		argc;
	int		i;
	int		j;

	argc = get_argc(*argv);
	new_argv = (char **)ft_calloc(argc - count_redirection + 1, sizeof(char *));
	if (!new_argv)
		return (-1);

	i = -1;
	j = -1;
	while ((*argv)[++i])
	{
		if ((*argv)[i] > (char *)10LL)
			new_argv[++j] = (*argv)[i];
		else
		{
			if ((*argv)[i + 1])				//TODO: test cases
				i += 1;
		}
	}

	/* if pipe.method 2, free each cmd.argv*/
	// free((*argv));
	(*argv) = new_argv;
	return (0);
}

/*
	1. If the command contains no slashes
		1-1. shell function
		1-2. corresponding built-in command
		1-3. searches $PATH for an executable

	2. If the command contains slashes, that named file is executed.
*/

//FIXIT: if (!slashes) { built-in -> PATH } else {excute argv}
static int has_slash(char *arg)
{
	if (ft_strchr(arg, '/'))
		return (1);
	return (0);
}

// t_exit	run(t_cmd cmd)
// {
// 	t_exit		ext;

// 	// get_argv_without_redirection(&cmd.argv, check_redirection(cmd.argv));

// 	// for (int i = 0; cmd.argv[i]; i++)
// 	// 	printf("new argv[%d] : %s\n", i, cmd.argv[i]);
// 	if (!cmd.path)
// 	{
// 		if (ft_strlen(cmd.argv[0]) == 4 && !ft_strncmp(cmd.argv[0], "exit", 4))
// 			return ((t_exit){PARENT_EXIT, __exit(cmd.argv)});
// 		else if (is_builtin(cmd.argv[0]))
// 			return ((t_exit){BUILTIN, run_builtin(cmd.argv)});
// 		else
// 		{
// 			if (has_slash(cmd.argv[0]))
// 				cmd.path = cmd.argv[0];
// 			else
// 				return ((t_exit){BUILTIN, ENOCMD});				/* Command not found */
// 		}
// 	}
// 	ext.pid = fork();
// 	ext.status = 0;
// 	if (ext.pid == CHILD)
// 	{
// 		if (execve(cmd.path, cmd.argv, environ) == -1)			/* if has slash and execve fail -> No such file or directory */
// 			ext.status = errno;
// 	}
// 	else if (ext.pid > 0)
// 		ext.pid = wait(&ext.status);
// 	return (ext);
// }


char *get_path(char *arg)
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

int	fill_path(t_cmd *cmd)
{
	if (has_slash(cmd->argv[0]))
		cmd->path = cmd->argv[0];
	else
	{
		if (is_builtin(cmd->argv[0]))			//NOTE:it includes __exit case
			cmd->path = "built-in";			//FIXME
		else
			cmd->path = get_path(cmd->argv[0]);	//NOTE:it includes ENOCMD case
	}

	return (0);
}


t_exit	run(t_cmd cmd)
{
	t_exit		ext;

	printf("cmd.path : %s\n", cmd.path);
	if (is_equal(cmd.path, "built-in"))	//FIXME:
	{
		if (is_equal("exit", cmd.argv[0]))
			return ((t_exit){PARENT_EXIT, __exit(cmd.argv)});
		else
			return ((t_exit){BUILTIN, run_builtin(cmd.argv)});
	}
	ext.pid = fork();
	ext.status = 0;
	if (ext.pid == CHILD)
	{
		if (execve(cmd.path, cmd.argv, environ) == -1)			/* if has slash and execve fail -> No such file or directory */
			ext.status = errno;
	}
	else if (ext.pid > 0)
		ext.pid = wait(&ext.status);
	return (ext);
}
	// return ((t_exit){BUILTIN, ENOCMD});				/* Command not found */

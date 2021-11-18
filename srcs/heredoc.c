/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:10:42 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/18 14:39:58 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

char	*write_until_env(int fd, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '$')
		{
			write(fd, &line[i], 2);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			tmp = itoa_(get_or_set_exitcode(GET, 0));
			ft_putstr_fd(tmp, fd);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1])
			break ;
		else
			write(fd, &line[i++], 1);
	}
	return (&line[i]);
}

/* expand environment variables */
char	*expand_env(int fd, char *line)
{
	int		i;
	char	*env_var;

	line = write_until_env(fd, line);
	i = 0;
	if (line[i] == '$' && !line[i + 1])
		return (line);
	else if (line[i] == '$' && line[++i])
	{
		env_var = getenv_(&line[i], &i, 1);
		if (!env_var)
			ft_putstr_fd("", fd);
		else
			ft_putstr_fd(env_var, fd);
	}
	return (&line[i]);
}

/* check for expand and trim quotes in delimiter */
int	heredoc_read(char **delim)
{
	int			fd;
	int			expand;
	char		*line;

	signal(SIGINT, SIG_DFL);
	expand = check_delimiter(delim);
	fd = open(TMP_HD_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || is_equal(line, *delim))
			break ;
		if (expand)
			line = expand_env(fd, line);
		ft_putendl_fd(line, fd);
	}
	close(fd);
	exit(0);
}

int	heredoc_status(int ext_status)
{
	if (WIFEXITED(ext_status) && WEXITSTATUS(ext_status) == -1)
	{
		ft_putendl_fd("error while reading heredoc", STDERR_FILENO);
		get_or_set_exitcode(SET, EXECUTION_FAILURE);
		return (MALLOCERR);
	}
	if (WIFSIGNALED(ext_status) && WTERMSIG(ext_status) == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		get_or_set_interactive(SET, ON);
		get_or_set_exitcode(SET, EXECUTION_FAILURE);
		return (HEREDOC_INTR);
	}
	return (0);
}

int	heredoc(t_cmd *cmd, char *delim)
{
	int			fd;
	int			e;
	t_exit		ext;

	get_or_set_interactive(SET, OFF);
	ext.pid = fork();
	if (ext.pid == CHILD)
		heredoc_read(&delim);
	else if (ext.pid > 0)
	{
		ext.pid = wait(&ext.status);
		e = heredoc_status(ext.status);
		if (e)
			return (e);
		fd = open(TMP_HD_FILE, O_RDONLY);
		if (cmd->redir_stream.in != DEFAULT)
			close(cmd->redir_stream.in);
		cmd->redir_stream.in = fd;
		return (EXECUTION_SUCCESS);
	}
	ft_putendl_fd("error while reading heredoc", STDERR_FILENO);
	get_or_set_exitcode(SET, EXECUTION_FAILURE);
	return (FORKERR);
}

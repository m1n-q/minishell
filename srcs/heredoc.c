/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:10:42 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/05 21:10:08 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

char	*write_until_env(int fd, char *line)
{
	int		i;
	int		cnt;
	char	*tmp;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '$')
		{
			write(fd, &line[i], 2);
			i += 2;
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			tmp = ft_itoa(get_or_set_exitcode(GET, 0));
			write(fd, tmp, ft_strlen(tmp));
			i += 2;
		}
		else if (getenv(&line[i + 1]))
			break ;
		else
			write(fd, &line[i++], 1);
	}
	return (&line[i]);
}

/* expand environment variables */
char	*expand_env(int fd, char *line)
{
	char	*env_var;

	line = write_until_env(fd, line);
	if (line[0] == '$' && !line[1])
		return (line);
	else if (line[0] == '$' && line[1] == '?')
		return (ft_itoa(get_or_set_exitcode(GET, 0)));
	else if (line[0] == '$' && line[1] && line[1] != '?')
	{
		env_var = getenv(&line[1]);
		if (!env_var)
		{
			write(fd, "\n", 1);
			return (0);
		}
		line = malloc(sizeof(char) * (ft_strlen(env_var) + 1));
		ft_strlcpy(line, env_var, ft_strlen(env_var) + 1);
	}
	return (line);
}

/* check for expand and trim quotes in delimiter */
int	check_delimiter(char **delim)
{
	int		i;
	int		len;
	char	*ret;
	char	*s;

	s = *delim;
	if (!(is_q(s[0]) && s[ft_strlen(s) - 1] == s[0]))
		return (1);
	i = 0;
	len = ft_strlen(s) - 2;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (len--)
	{
		if (is_q(*s))
			s++;
		ret[i++] = *s++;
	}
	ret[i] = 0;
	free(*delim);
	*delim = ret;
	return (0);
}

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

int	heredoc(t_cmd *cmd, char *delim)
{
	int			fd;
	t_exit		ext;

	get_or_set_interactive(SET, OFF);
	ext.pid = fork();
	if (ext.pid == CHILD)
		heredoc_read(&delim);
	else if (ext.pid > 0)
	{
		ext.pid = wait(&ext.status);
		if (WIFSIGNALED(ext.status) && WTERMSIG(ext.status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			get_or_set_interactive(SET, ON);
			get_or_set_exitcode(SET, EXECUTION_FAILURE);
			return (HEREDOC_INTR);
		}
		fd = open(TMP_HD_FILE, O_RDONLY);
		if (cmd->redir_stream.in != DEFAULT)
			close(cmd->redir_stream.in);
		cmd->redir_stream.in = fd;
		return (EXECUTION_SUCCESS);
	}
	get_or_set_exitcode(SET, EXECUTION_FAILURE);
	return (FORKERR);
}

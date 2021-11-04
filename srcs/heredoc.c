/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:10:42 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/04 16:25:44 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* check if eof is surrounded by quotes */
int	check_eof(char *eof)
{
	if (is_q(eof[0]) && eof[ft_strlen(eof) - 1] == eof[0])
		return (0);
	return (1);
}

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

/* trim quotes in eof delimiter */
char	*trim_q(char *eof)
{
	int		i;
	int		len;
	char	*ret;

	if (check_eof(eof))
		return (eof);
	i = 0;
	len = ft_strlen(eof) - 2;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (len--)
	{
		if (is_q(*eof))
			eof++;
		ret[i++] = *eof++;
	}
	ret[i] = 0;
	return (ret);
}

int	heredoc(t_cmd *cmd, char *eof)
{
	int		fd;
	int		expand;
	char	*line;

	get_or_set_interactive(SET, ON_HD);
	expand = check_eof(eof);
	eof = trim_q(eof);
	fd = open(TMP_HD_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
		if (line && *line == EOF)
		{
			get_or_set_interactive(SET, ON);
			get_or_set_exitcode(SET, EXECUTION_FAILURE);
			rl_done = 0;
			return (HEREDOC_INTR);
		}
		if (!line)
			break ;
		if (is_equal(line, eof))
			break ;
		if (expand)
			line = expand_env(fd, line);
		ft_putendl_fd(line, fd);
	}
	close(fd);
	fd = open(TMP_HD_FILE, O_RDONLY);
	if (cmd->redir_stream.in != DEFAULT)
		close(cmd->redir_stream.in);
	cmd->redir_stream.in = fd;
	return (0);
}

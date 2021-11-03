/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:10:42 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/03 14:48:40 by kyumlee          ###   ########.fr       */
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

/* expand environment variables */
char	*expand_env(int fd, char *line)
{
	char	*env_var;

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

int	heredoc(char *eof)
{
	int		fd;
	int		expand;
	char	*line;

	expand = check_eof(eof);
	eof = trim_q(eof);
	fd = open(TMP_HD_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline("> ");
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
	return (fd);
}

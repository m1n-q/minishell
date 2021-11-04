/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:15 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/04 20:45:43 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if a string contains a pipe or redirection
 * maybe we can use a function from libft */
int	check_pipe_redir(char *s)
{
	while (*s)
	{
		if (is_pipe_rin_rout(*s))
			return (1);
		s++;
	}
	return (0);
}

/* count the number of pipes and redirections */
void	cnt_pipe_redir(char *s, int *cnt)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (is_q(s[i]))
			i += skip_q(&s[i]);
		if (is_pipe_rin_rout(s[i]) && s[i] != s[i + 1])
		{
			if (i > 0 && !ft_isspace(s[i - 1]) && s[i] != s[i - 1])
				(*cnt)++;
			if (s[i + 1] && !ft_isspace(s[i + 1]))
				(*cnt)++;
		}
		else if (is_pipe_rin_rout(s[i]) && s[i] == s[i + 1])
		{
			if (i > 0 && !ft_isspace(s[i - 1]) && s[i] != s[i - 1])
				(*cnt)++;
			if (s[i + 2] && !ft_isspace(s[i + 2]))
				(*cnt)++;
			i++;
		}
		i++;
	}
}

/* insert space before and after the pipes and redirections
 * if they are not separated by space within a string */
void	cpy_pipe_redir(char *s, char *argv, int *i, int *j)
{
	if (*j > 0 && s[(*j) - 1] != s[*j] && !ft_isspace(s[(*j) - 1]))
		argv[(*i)++] = ' ';
	argv[(*i)++] = s[(*j)++];
	if (*j > 0 && s[*j] && s[*j] == s[(*j) - 1])
		argv[(*i)++] = s[(*j)++];
	if (!ft_isspace(s[*j]))
		argv[(*i)++] = ' ';
}

/* insert spaces between the pipes and redirections in the original string */
void	cpy_with_space(char *s, int len, char *argv, int i)
{
	int		j;
	char	c;

	j = 0;
	while (i < len)
	{
		if (is_q(s[j]))
		{
			c = s[j];
			argv[i++] = s[j++];
			while (s[j] && s[j] != c)
				argv[i++] = s[j++];
			argv[i++] = s[j++];
		}
		else if (is_pipe_rin_rout(s[j]))
			cpy_pipe_redir(s, argv, &i, &j);
		else
			argv[i++] = s[j++];
	}
	argv[len] = 0;
}

char	*split_pipe_redir(char *s)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	if (!check_pipe_redir(s))
		return (s);
	cnt_pipe_redir(s, &len);
	len += (int)ft_strlen(s);
	if (!len)
		return (s);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (0);
	cpy_with_space(s, len, ret, i);
	return (ret);
}

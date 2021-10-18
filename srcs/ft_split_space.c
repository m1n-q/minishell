/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:05:55 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/18 15:33:00 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* parsing pipe and redirections */
char	*pipe_redir(char *s)		//FIXME: free org "s" if changed
{
	if (ft_strlen(s) == 1)
	{
		if (*s == '|')
			s = (char *)PIPE;
		else if (*s == '<')
			s = (char *)REDIRECT_IN;
		else if (*s == '>')
			s = (char *)REDIRECT_OUT;
	}
	else if (ft_strlen(s) == 2)
	{
		if (*s == '<' && *(s + 1) == '<')
			s = (char *)HEREDOC;
		if (*s == '>' && *(s + 1) == '>')
			s = (char *)REDIRECT_APPEND;
	}
	return (s);
}

char	**ft_split_space(char *s)
{
	int		i;
	int		str_len;
	char	**ret;

	if (!check_quotes(s))
		return (0);
	ret = malloc_strs(s);
	i = 0;
	str_len = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			str_len = cnt_str_len(s);
			ret[i] = malloc_str(s, ret, i, str_len);
			ret[i] = cpy_str(s, ret[i]);
			ret[i] = pipe_redir(ret[i]);
			s += str_len;
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

/*char	**split_space_tmp(char const *s, t_cmd *cmd)
{
	char	**ret;
	int		i;

	if (!s)
		return (0);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (cnt_s(s) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			ret[i] = (char *)malloc(sizeof(char) * (cnt_s_len(s, cmd) + 1));
			if (!ret[i])       					// have to free prev malloced
				return (0);
			if (*s == '"' || *s == '\'')			// add single quote
				ft_strlcpy(ret[i], s + 1, cnt_s_len(s, cmd) - 1);
			else
				ft_strlcpy(ret[i], s, cnt_s_len(s, cmd) + 1);
			s += cnt_s_len(s, cmd);
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}*/

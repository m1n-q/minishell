/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:50 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 17:46:27 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	is_q(char c)
{
	return (c == '"' || c == '\'');
}

int	is_pipe_redir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*calloc_n_lcpy(char *s, size_t dstsize)
{
	char	*ret;

	ret = (char *)calloc_(dstsize, sizeof(char));
	ft_strlcpy(ret, s, dstsize);
	return (ret);
}

/* getenv with length */
char	*getenv_(char *s, int *i, int check)
{
	char	*tmp;
	char	*ret;
	int		j;

	j = 0;
	while (ft_isdigit(s[j]) || ft_isalpha(s[j]) || s[j] == '_')
		j++;
	tmp = calloc_n_lcpy(s, j + 1);
	ret = getenv(tmp);
	free(tmp);
	if (!ret)
		ret = EMPTY_VAR;
	if (check)
		*i = ++j;
	return (ret);
}

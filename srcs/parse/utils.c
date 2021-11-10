/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:50 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 17:17:07 by mishin           ###   ########.fr       */
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

int	is_empty_q(char *s)
{
	if (*s && *(s + 1) && is_q(*s) && *s == *(s + 1))
		return (1);
	return (0);
}

char	*calloc_n_lcpy(char *s, size_t dstsize)
{
	char	*ret;

	ret = (char *)calloc_(dstsize, sizeof(char));
	ft_strlcpy(ret, s, dstsize);
	return (ret);
}

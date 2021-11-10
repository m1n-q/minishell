/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:50 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 13:49:04 by kyumlee          ###   ########.fr       */
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

int	is_pipe_rin_rout(char c)
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

	ret = (char *)ft_calloc(dstsize, sizeof(char));
	if (!ret)
		exit (1);
	ft_strlcpy(ret, s, dstsize);
	return (ret);
}

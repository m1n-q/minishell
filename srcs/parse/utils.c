/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:50 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/01 16:01:51 by kyumlee          ###   ########.fr       */
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

/* check if there is a q mark in the string */
int	has_q(char *s)
{
	while (*s)
	{
		if (is_q(*s))
			return (1);
		s++;
	}
	return (0);
}

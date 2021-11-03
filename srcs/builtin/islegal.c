/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islegal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:49:52 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 20:01:16 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	legal_variable_starter(char c)
{
	return (ft_isalpha(c) || (c == '_'));
}

int	legal_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	legal_identifier(char *name)
{
	register char	*s;
	unsigned char	c;

	if (!name || !(*name) || (legal_variable_starter(*name) == 0))
		return (0);
	s = name + 1;
	c = *s;
	while (c)
	{
		if (legal_variable_char(c) == 0)
			return (0);
		c = *(++s);
	}
	return (1);
}

int	legal_number(char *string, intmax_t *result)
{
	intmax_t	value;
	char		*ep;

	if (result)
		*result = 0;
	errno = 0;
	value = ft_strtoimax(string, &ep);
	if (errno)
		return (0);
	while (whitespace(*ep))
		ep++;
	if (string && *string && *ep == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}

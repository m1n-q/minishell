/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islegal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:49:52 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:35:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

intmax_t	strtoimax(char *str, char **ep, int base)
{
	(void)str;
	(void)ep;
	(void)base;

	return (0);
}

int legal_variable_starter(char c)
{
	return (isalpha(c) || (c == '_'));
}

int legal_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int legal_identifier(char *name)
{
	register char	*s;
	unsigned char	c;

	if (!name || !(c = *name) || (legal_variable_starter(c) == 0))
		return (0);
	for (s = name + 1; (c = *s) != 0; s++)
	{
		if (legal_variable_char(c) == 0)
			return (0);
	}
	return (1);
}

int	legal_number(char *string, intmax_t *result)
{
	intmax_t value;
	char *ep;
	if (result)
		*result = 0;
	errno = 0;
	value = ft_strtoimax(string, &ep);
	if (errno)
		return (0); /* errno is set on overflow or underflow */

	/* Skip any trailing whitespace, since strtoimax does not. */
	while (whitespace(*ep))
		ep++;

	/* If *string is not '\0' but *ep is '\0' on return, the entire string
  ​     is valid. */
	if (string && *string && *ep == '\0')
	{
		if (result)
			*result = value;
		return (1);
	}
	return (0);
}


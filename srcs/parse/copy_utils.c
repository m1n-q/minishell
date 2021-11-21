/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:10:04 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/21 22:33:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if an arg has a dollar-sign */
int	expand(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			c = s[i];
			while (s[++i] != c)
				;
		}
		else if (s[i] == '"')
		{
			c = s[i];
			while (s[++i] != c)
				if (s[i] == '$')
					return (i);
		}
		else if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	get_end_index(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

int	was_expanded(char *s)
{
	int	i;
	int	end;

	i = -1;
	end = get_end_index(s);
	while (++i < end)
		if (s[i] == '$')
			return (1);
	return (0);
}

int	has_quotes(char *s)
{
	int	i;
	int	end;

	i = -1;
	end = get_end_index(s);
	while (++i < end)
	{
		if (s[i] == '\'')
			return (SINGLE_Q);
		else if (s[i] == '"')
			return (DOUBLE_Q);
	}
	return (0);
}

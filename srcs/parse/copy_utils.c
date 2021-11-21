/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:10:04 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/21 17:11:24 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if an arg has a dollar-sign */
int	has_dollar_sign(char *s)
{
	int		i;
	char	c;

	i = -1;
	if (s[0] == '$' && ft_isspace(s[1]))
		return (0);
	while (s[++i] && !is_q(s[i]) && !ft_isspace(s[i]))
		if (s[i] == '$')
			return (1);
	if (ft_isspace(s[i]))
		return (0);
	if (is_q(s[i]))
	{
		c = s[i];
		while (s[++i] != c)
			if (s[i] == '$')
				return (1);
		i++;
	}
	return (0);
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
		if (is_q(s[i]))
			return (1);
	return (0);
}

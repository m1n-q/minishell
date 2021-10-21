/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:58:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/21 17:02:47 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	is_q(char c)
{
	return (c == '"' || c == '\'');
}

/* if the numbers of each quotes are odd (mismatch) return 0,
 * otherwise return 1 */
int	quotes_match(char *s)
{
	char	c;
	int		cnt_q;

	cnt_q = 0;
	while (*s)
	{
		if (is_q(*s))
		{
			c = *s++;
			cnt_q++;
			while (*s)
			{
				if (*s == c)
				{
					cnt_q--;
					break ;
				}
				s++;
			}
		}
		s++;
	}
	return (1);
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

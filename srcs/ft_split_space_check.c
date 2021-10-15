/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:58:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/15 18:41:50 by kyumlee          ###   ########.fr       */
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

/* check the quotes. if match return 0, if not return 1 */
int	check_pairs(char *s, char c)
{
	int	ret;

	ret = 0;
	if (!is_q(*s))
		return (ret);
	if (*s == c)
	{
		ret++;
		s++;
		while (*s)
		{
			if (*s == c)
			{
				ret--;
				break ;
			}
			s++;
		}
	}
	return (ret);
}

/* if the return value of the above function is 1, return 0 */
int	check_quotes(char *s)
{
	int	cnt_q;

	while (*s)
	{
		if (is_q(*s))
			break ;
		s++;
	}
	cnt_q = check_pairs(s, *s);
	if (cnt_q)
		return (0);
	return (1);
}

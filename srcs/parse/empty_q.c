/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_q.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:46:59 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/03 11:49:07 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* count empty sets of quotes */
int	cnt_empty_q(char *s)
{
	int		ret;

	ret = 0;
	while (*s)
	{
		if (is_empty_q(s) && *(s + 2) && !ft_isspace(*(s + 2)))
		{
			ret++;
			s += 2;
		}
		else
			s++;
	}
	return (ret);
}

/* remove all empty sets of quotes */
char	*rm_empty_q(char *s)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = ft_strlen(s) - cnt_empty_q(s) * 2;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (is_empty_q(s) && *(s + 2) && !ft_isspace(*(s + 2)))
			s += 2;
		else
			ret[i++] = *s++;
		if (!*s)
			break ;
	}
	ret[i] = 0;
	return (ret);
}

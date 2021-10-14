/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:05:55 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/15 00:22:42 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

char	**ft_split_space(char *s)
{
	int		i;
	int		str_len;
	char	**ret;

	if (!check_quotes(s))
		return (0);
	ret = malloc_strs(s);
	i = 0;
	str_len = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			str_len = cnt_str_len(s);
			ret[i] = malloc_str(s, ret, i, str_len);
			ret[i] = cpy_str(s, ret[i]);
			s += str_len;
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

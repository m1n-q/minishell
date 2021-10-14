/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 20:05:55 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/14 20:46:19 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

char	**split_space_tmp(char const *s, t_cmd *cmd)
{
	char	**ret;
	int		i;

	if (!s)
		return (0);
	i = 0;
	ret = (char **)malloc(sizeof(char *) * (cnt_s(s) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			ret[i] = (char *)malloc(sizeof(char) * (cnt_s_len(s, cmd) + 1));
			if (!ret[i])       					/* have to free prev malloced */
				return (0);
			if (*s == '"' || *s == '\'')			/* add single quote */
				ft_strlcpy(ret[i], s + 1, cnt_s_len(s, cmd) - 1);
			else
				ft_strlcpy(ret[i], s, cnt_s_len(s, cmd) + 1);
			s += cnt_s_len(s, cmd);
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

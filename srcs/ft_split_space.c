/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:12:58 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/13 19:49:52 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"
#include "./../incs/libft.h"

char	**ft_split_space(char const *s, t_cmd *cmd)
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
			if (!ret[i])
				return (0);
			if (*s == '"')
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

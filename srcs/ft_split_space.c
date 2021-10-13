/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:12:58 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/13 15:05:07 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
			|| c == '\n' || c == '\v' || c == '\f');
}

int	cnt_s(char const *s)
{
	int	ret;

	ret = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isspace(*s) && (ft_isspace(*(s + 1)) || !*(s + 1)))
			ret++;
		s++;
	}
	return (ret);
}

int	cnt_s_len(char const *s)
{
	int		ret;
	char	*tmp;

	tmp = (char *)s;
	ret = 0;
	while (ft_isspace(*tmp))
		tmp++;
	while (*tmp)
	{
		if (!ft_isspace(*tmp))
			ret++;
		else
			break ;
		tmp++;
	}
	return (ret);
}

char	**ft_split_space(char const *s)
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
			ret[i] = (char *)malloc(sizeof(char) * (cnt_s_len(s) + 1));
			if (!ret[i])
				return (0);
			ft_strlcpy(ret[i], s, cnt_s_len(s) + 1);
			s += cnt_s_len(s);
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_strs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:58:17 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/16 15:26:48 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* skip q marks when counting how many strings there are */
char	*skip_q(char *s, char c)
{
	s++;
	while (*s)
	{
		if (*s == c)
			break ;
		s++;
	}
	s++;
	return (s);
}

/* count how many strings there are */
int	cnt_strs(char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (*s)
	{
		if (*s && !ft_isspace(*s))
		{
			ret++;
			if (is_q(*s) && (*s == s[0] || (*s && ft_isspace(*(s - 1)))))
				s = skip_q(s, *s);
			while (*s && !ft_isspace(*s))
			{
				if (is_q(*s))
					s = skip_q(s, *s);
				else
					s++;
			}
		}
		while (ft_isspace(*s))
			s++;
	}
	return (ret);
}

/* malloc strings */
char	**malloc_strs(char *s)
{
	int		num_of_strs;
	char	**ret;

	num_of_strs = cnt_strs(s);
	ret = malloc(sizeof(char *) * (num_of_strs + 1));
	if (!ret)
		return (0);
	return (ret);
}

void	free_strs(char **ret, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(ret[j]);
	free(ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:31 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 13:50:28 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* skip q marks when counting how many strings there are */
int	skip_q(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[i++];
	while (s[i] != c)
		i++;
	i++;
	return (i);
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
				s += skip_q(s);
			while (*s && !ft_isspace(*s))
			{
				if (is_q(*s))
					s += skip_q(s);
				else
					s++;
			}
		}
		while (ft_isspace(*s))
			s++;
	}
	return (ret);
}

/* memory allocations of strings */
char	**malloc_strs(char *s)
{
	int		num_of_strs;
	char	**ret;

	num_of_strs = cnt_strs(s);
	ret = (char **)ft_calloc(num_of_strs + 1, sizeof(char *));
	if (!ret)
		return (0);
	return (ret);
}

void	free_strs(char **argv, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(argv[j]);
	free(argv);
}

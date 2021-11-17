/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:31 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/17 16:21:11 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* skip q marks when counting how many strings there are */
int	skip_q(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (is_q(s[i]))
	{
		c = s[i++];
		while (s[i] != c)
			i++;
		i++;
	}
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i);
}

/* count how many strings there are */
void	cnt_strs(char *s, int *ret)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_q(s[i]) && !ft_isspace(s[i]))
		{
			(*ret)++;
			while (s[i] && !ft_isspace(s[i]))
			{
				if (is_q(s[i]))
					i += skip_q(&s[i]) - 1;
				i++;
			}
		}
		if (is_q(s[i]))
		{
			(*ret)++;
			i += skip_q(&s[i]);
		}
		while (ft_isspace(s[i]))
			i++;
	}
}

/* memory allocations of strings */
char	**malloc_strs(char *s)
{
	int		num_of_strs;
	char	**ret;

	num_of_strs = 0;
	cnt_strs(s, &num_of_strs);
	ret = (char **)calloc_(num_of_strs + 1, sizeof(char *));
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

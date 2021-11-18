/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:31 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/18 22:44:13 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* skip quotes when counting how many args there are */
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

/* count how many args there are */
void	cnt_strs(char *s, int *ret)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_q(s[i]) && !ft_isspace(s[i]))
		{
			(*ret)++;
			if (env_has_space(getenv_(&s[i + 1], &i, 0), s[i]))
				*ret += env_has_space(getenv_(&s[i + 1], &i, 0), s[i]);
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

/* memory allocations of argv */
char	**malloc_strs(char *s, int *argc)
{
	char	**ret;

	cnt_strs(s, argc);
	ret = (char **)calloc_(*argc + 1, sizeof(char *));
	return (ret);
}

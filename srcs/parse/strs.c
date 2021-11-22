/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:31 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 18:14:46 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* skip quotes when counting how many args there are */
int	skip_q(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[i++];
	while (s[i] && s[i] != c)
		i++;
	i++;
	return (i);
}

int	count_n_skip_env(char *s, char c, int *argc)
{
	int		i;
	char	*env;

	i = 0;
	i++;
	env = getenv_(&s[i], &i, 0);
	if (ft_isspace(s[i]) || !s[i])
		(*argc)++;
	*argc += env_has_space(env, c);
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		i++;
	return (i);
}

int	count_n_skip(char *s, int *argc)
{
	int	i;

	i = 0;
	(*argc)++;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))
			i += skip_q(&s[i]) - 1;
		if (s[i] == '$')
		{
			if (i > 0 && s[i - 1] && !ft_isspace(s[i - 1]))
			{
				if (has_leading_space(getenv_(&s[i + 1], NULL, 0)))
					*argc += 1;
			}
			if (s[next_idx(s, i + 1)] && !ft_isspace(s[next_idx(s, i + 1)]))
			{
				if (has_trailing_space(getenv_(&s[i + 1], NULL, 0)))
					*argc += 1;
			}
			i += count_n_skip_env(&s[i], s[i], argc) - 1;
		}
		i++;
	}
	return (i);
}

/* count how many args there are */
void	cnt_strs(char *s, int *argc)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && !ft_isspace(s[i]))
			i += count_n_skip(&s[i], argc);
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

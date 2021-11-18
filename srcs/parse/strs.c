/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:31 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/19 03:00:13 by kyumlee          ###   ########.fr       */
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

int	count_n_skip_env(char *s, char c, int *ret)
{
	int		i;
	char	*env;

	i = 1;
	env = getenv_(&s[i], &i, 0);
	*ret = env_has_space(env, c);
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		i++;
	return (i);
}

int	count_n_skip_default(char *s, int *ret)
{
	int	i;

	i = 0;
	(*ret)++;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))
			i += skip_q(&s[i]) - 1;
		i++;
	}
	return (i);
}

/* count how many args there are */
void	cnt_strs(char *s, int *ret)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			i += count_n_skip_env(&s[i], s[i], ret);
		if (s[i] != '$' && !is_q(s[i]) && !ft_isspace(s[i]))
			i += count_n_skip_default(&s[i], ret);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_with_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/17 19:30:38 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	env_has_space(char *s, char c)
{
	int	i;

	if (s == EMPTY_VAR)
		return (0);
	i = -1;
	if (c != '$')
		return (0);
	while (s[++i])
	{
		if (ft_isspace(s[i]))
			return (1);
	}
	return (0);
}

char	**split_and_join_till(char *arg, char **argv, int *i)
{
	char	**ret;
	char	**tmp;
	int		j;
	int		tmp_i;

	tmp = ft_split(arg, ' ');
	ret = calloc_(get_argc(tmp) + *i + 1, sizeof(char **));
	j = -1;
	while (++j < *i)
	{
		if (is_token(argv[j]) || argv[j] == EMPTY_VAR)
			ret[j] = argv[j];
		else
			ret[j] = ft_strdup(argv[j]);
	}
	tmp_i = -1;
	while (++tmp_i < get_argc(tmp))
		ret[j++] = ft_strdup(tmp[tmp_i]);
	*i = j;
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(tmp), tmp);
	free(tmp);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/11 18:03:46 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	env_has_space(char c, char *s)
{
	int	i;

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
	ret = calloc_(get_argc(tmp) + get_argc(argv), sizeof(char **));
	j = -1;
	while (++j < *i - 1)
		ret[j] = ft_strdup(argv[j]);
	tmp_i = -1;
	while (++tmp_i < get_argc(tmp))
		ret[j++] = ft_strdup(tmp[tmp_i]);
	*i = j;
	free_till(get_argc(argv), argv);
	free(argv);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/18 21:37:56 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if env_var_value has space */
int	env_has_space(char *s, char c)
{
	int	i;
	int	cnt_space;

	if (s == EMPTY_VAR)
		return (0);
	i = -1;
	cnt_space = 0;
	if (c != '$')
		return (0);
	while (s[++i])
	{
		if (ft_isspace(s[i]) && s[i + 1] && !ft_isspace(s[i + 1]))
			cnt_space++;
	}
	return (cnt_space);
}

/* split env_var_value with space and join it to the original argv */
char	**split_and_join_till(char *arg, char **argv, int *i, int argc)
{
	int		j;
	int		tmp_i;
	char	**tmp;
	char	**ret;

	tmp = ft_split(arg, ' ');
	ret = calloc_(argc + 1, sizeof(char **));
	j = -1;
	tmp_i = -1;
	while (++j < *i)
	{
		if (is_token(argv[j]) || argv[j] == EMPTY_VAR)
			ret[j] = argv[j];
		else
			ret[j] = dup_and_free(argv[j]);
	}
	while (++tmp_i < get_argc(tmp))
		ret[j++] = dup_and_free(tmp[tmp_i]);
	*i = j;
	free(argv);
	free(tmp);
	return (ret);
}

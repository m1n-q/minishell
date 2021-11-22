/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:19:20 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 14:28:20 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	double_q_length(char *arg)
{
	int		i;
	char	c;

	i = 0;
	c = arg[i];
	while (arg[++i] != c)
		;
	i++;
	return (i);
}

void	copy_till(char *arg, char **new_arg, int i)
{
	char	*tmp;

	tmp = calloc_n_lcpy(arg, i + 1);
	if (*new_arg)
		*new_arg = join_and_free(*new_arg, tmp, 3);
	else
		*new_arg = dup_and_free(tmp);
}

int	copy_single_quotes(char *arg, char **new_arg)
{
	int		i;
	char	c;

	i = 0;
	c = arg[i];
	while (arg[++i] != c)
		;
	i++;
	copy_till(arg, new_arg, i);
	return (i);
}

int	copy_double_quotes(char *arg, char **new_arg, char *prev_arg)
{
	int		i;
	int		j;
	int		count;
	int		ret;

	ret = double_q_length(arg);
	count = count_env(arg);
	j = -1;
	while (++j < count)
	{
		i = 0;
		while (arg[i] != '$')
			i++;
		copy_till(arg, new_arg, i);
		arg += copy_env_val(&arg[i], new_arg, prev_arg) + i;
	}
	i = 0;
	if (!count)
		i++;
	while (arg[i] != '"')
		i++;
	copy_till(arg, new_arg, i);
	*new_arg = join_and_free(*new_arg, "\"", 1);
	return (ret);
}

int	copy_quotes(char *arg, char **new_arg, char *prev_arg)
{
	if (*arg == '\'')
		return (copy_single_quotes(arg, new_arg));
	else if (*arg == '"')
		return (copy_double_quotes(arg, new_arg, prev_arg));
	return (0);
}

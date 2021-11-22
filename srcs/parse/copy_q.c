/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:19:20 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 19:06:01 by kyumlee          ###   ########.fr       */
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

int	copy_till(char *arg, char **new_arg, int i)
{
	char	*tmp;

	tmp = calloc_n_lcpy(arg, i + 1);
	if (*new_arg && !is_empty(*new_arg))
		*new_arg = join_and_free(*new_arg, tmp, 3);
	else if (!*new_arg || is_empty(*new_arg))
		*new_arg = dup_and_free(tmp);
	return (i);
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

int	copy_double_quotes(char *arg, char **new_arg, char *prev_arg, char q)
{
	int		i;
	int		count;
	int		ret;

	count = count_env(arg);
	ret = double_q_length(arg);
	if (!count)
		return (copy_till(arg, new_arg, ret));
	while (count--)
	{
		i = 0;
		while (arg[i] != '$')
			i++;
		copy_till(arg, new_arg, i);
		arg += copy_env_val(&arg[i], new_arg, prev_arg, q) + i;
	}
	if (*new_arg == (char *)AMBIG_REDIR)
		return (ret);
	i = 0;
	while (arg[i] != '"')
		i++;
	copy_till(arg, new_arg, i);
	*new_arg = join_and_free(*new_arg, "\"", 1);
	return (ret);
}

int	copy_quotes(char *arg, char **new_arg, char *prev_arg, char q)
{
	if (*arg == '\'')
		return (copy_single_quotes(arg, new_arg));
	else if (*arg == '"')
		return (copy_double_quotes(arg, new_arg, prev_arg, q));
	return (0);
}

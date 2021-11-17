/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_non_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/17 21:58:21 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	join_non_env(char *s, char **p_arg)
{
	char	*tmp;
	int		i;

	i = 0;
	if (s[i] == '\'')
		i++;
	while (s[i] && s[i] != '$' && !is_q(s[i]))
		i++;
	tmp = calloc_n_lcpy(s, i + 1);
	if (*p_arg)
	{
		if (*p_arg != EMPTY_VAR)
			*p_arg = join_and_free(*p_arg, tmp, 3);
		else
			*p_arg = dup_and_free(tmp);
	}
	else
		*p_arg = dup_and_free(tmp);
	return (i);
}

int	join_dollar_at_end(char **p_arg)
{
	if (*p_arg)
	{
		if (*p_arg != EMPTY_VAR)
			*p_arg = join_and_free(*p_arg, "$", 1);
		else
			*p_arg = strdup_("$");
	}
	else
		*p_arg = strdup_("$");
	return (1);
}

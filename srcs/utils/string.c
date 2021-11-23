/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:24:02 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 15:25:36 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_or_dup(char *nullable, char *dupable)
{
	char	*ret;

	if (nullable != NULL)
		ret = strjoin_(nullable, dupable);
	else
		ret = strdup_(dupable);
	return (ret);
}

char	*joinjoin(char *a, char *b, char *c)
{
	char	*tmp;
	char	*ret;

	tmp = strjoin_(a, b);
	ret = strjoin_(tmp, c);
	free(tmp);
	return (ret);
}

char	*join_and_free(char *s1, char *s2, int tofree)
{
	char	*ret;

	if (!s1)
		ret = strdup_(s2);
	else if (!s2 || is_empty(s2))
		ret = strdup_(s1);
	else
		ret = strjoin_(s1, s2);
	if (tofree == 0)
		return (ret);
	else if (tofree == 1)
		free(s1);
	else if (tofree == 2)
		free(s2);
	else if (tofree == 3)
	{
		free(s1);
		free(s2);
	}
	return (ret);
}

char	*dup_and_free(char *s)
{
	char	*ret;

	ret = strdup_(s);
	free(s);
	return (ret);
}

char	*strlower_(char *str)
{
	char	*ret;
	int		i;

	ret = strdup_(str);
	i = -1;
	while (ret[++i])
		ret[i] = ft_tolower(ret[i]);
	return (ret);
}

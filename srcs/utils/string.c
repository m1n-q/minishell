/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:24:02 by mishin            #+#    #+#             */
/*   Updated: 2021/11/10 15:48:00 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && \
		!ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

char	*join_or_dup(char *nullable, char *dupable)
{
	char	*ret;

	if (nullable != NULL)
		ret = ft_strjoin(nullable, dupable);
	else
		ret = ft_strdup(dupable);
	return (ret);
}

char	*joinjoin(char *a, char *b, char *c)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(a, b);
	ret = ft_strjoin(tmp, c);
	free(tmp);
	return (ret);
}

char	*join_and_free(char *s1, char *s2, int tofree)
{
	char	*ret;

	if (!s1)
		ret = ft_strdup(s2);
	else if (!s2)
		ret = ft_strdup(s1);
	else
		ret = ft_strjoin(s1, s2);
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

	ret = ft_strdup(s);
	free(s);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:10:27 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 14:22:30 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*calloc_(size_t count, size_t size)
{
	void	*ret;

	ret = ft_calloc(count, size);
	if (!ret)
		exit_(-1);
	return (ret);
}

char	*strdup_(char *s)
{
	char	*ret;

	if (!s)
		return (s);
	if (is_empty(s))
		return (EMPTY_VAR);
	ret = ft_strdup(s);
	if (!ret)
		exit_(-1);
	return (ret);
}

char	*strjoin_(const char *s1, const char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (!ret)
		exit_(-1);
	return (ret);
}

char	*itoa_(int nbr)
{
	char	*ret;

	ret = ft_itoa(nbr);
	if (!ret)
		exit_(-1);
	return (ret);
}

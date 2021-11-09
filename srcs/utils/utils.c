/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:49:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/09 19:06:53 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinjoin(char *a, char *b, char *c)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(a, b);
	ret = ft_strjoin(tmp, c);
	free(tmp);
	return (ret);
}

int	get_argc(char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

int	is_equal(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) && \
		!ft_strncmp(s1, s2, ft_strlen(s1)))
		return (1);
	return (0);
}

int	skip_space(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (!*s)
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

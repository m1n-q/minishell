/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:14:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/21 17:14:25 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	has_leading_space(char *s)
{
	if (!s || s == EMPTY_VAR || !*s)
		return (0);
	if (ft_isspace(s[0]))
		return (1);
	return (0);
}

int	has_trailing_space(char *s)
{
	if (!s || s == EMPTY_VAR || !*s)
		return (0);
	if (ft_isspace(s[ft_strlen(s) - 1]))
		return (1);
	return (0);
}

int	next_idx(char *s, int cur)
{
	while (ft_isalpha(s[cur]) || ft_isdigit(s[cur]) || s[cur] == '_')
		cur++;
	return (cur);
}

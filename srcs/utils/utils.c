/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:49:25 by mishin            #+#    #+#             */
/*   Updated: 2021/11/10 13:57:06 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(char **argv)
{
	int	len;

	len = 0;
	while (argv[len])
		len++;
	return (len);
}

int	skip_space(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (1);
	return (0);
}

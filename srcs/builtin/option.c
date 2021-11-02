/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:24:18 by mishin            #+#    #+#             */
/*   Updated: 2021/11/02 21:03:05 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isoption(char *s, int optlen)
{
	if (optlen == TIL_SEC)
		return (s[0] == '-' && s[1] && s[1] != '-' && !s[2]);
	else if (optlen == TIL_END)
		return (s[0] == '-' && s[1]);
	else
		return (0);
}

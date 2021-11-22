/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_trimmer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:02:41 by mishin            #+#    #+#             */
/*   Updated: 2021/11/22 16:04:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_if_on_q(int *on_sq, int *on_dq, char q)
{
	if (q == '\'')
	{
		if (!*on_dq && !*on_sq)
			*on_sq = 1;
		else
			*on_sq = 0;
	}
	if (q == '"')
	{
		if (!*on_sq && !*on_dq)
			*on_dq = 1;
		else
			*on_dq = 0;
	}
}

static char	*where_to_trim(char *s, int *trimcount)
{
	int		i;
	int		on_dq;
	int		on_sq;
	int		count;
	char	*trim_index;

	trim_index = (char *)calloc_(ft_strlen(s) + 1, sizeof(char));
	i = 0;
	on_sq = 0;
	on_dq = 0;
	count = 0;
	while (s[i])
	{
		if (is_q(s[i]))
		{
			check_if_on_q(&on_sq, &on_dq, s[i]);
			if ((s[i] == '\'' && !on_dq) || \
				(s[i] == '"' && !on_sq))
				count += ++trim_index[i];
		}
		i++;
	}
	*trimcount = count;
	return (trim_index);
}

char	*quotes_trimmer(char *s)
{
	int		i;
	int		j;
	int		trimcount;
	char	*trim_index;
	char	*trimmed_str;

	trim_index = where_to_trim(s, &trimcount);
	trimmed_str = NULL;
	trimmed_str = (char *)calloc_(ft_strlen(s) - trimcount + 1, sizeof(char));
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (!trim_index[i])
			trimmed_str[j++] = s[i];
	}
	free(trim_index);
	return (trimmed_str);
}

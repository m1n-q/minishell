/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_strs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 23:58:17 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/15 19:01:50 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

/* when counting how many strings there are, skip the quotes. */
int	skip_q(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	i++;
	return (i);
}

/* count how many words there are
 * MODIFICATION NEEDED!! (for input case: [a' "w" ']) */
int	cnt_strs(char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] && !ft_isspace(s[i]))
		{
			ret++;
			if (is_q(s[i]) && (i == 0 || (ft_isspace(s[i - 1]) && i > 0)))
				i += skip_q(&s[i], s[i]);
			while (s[i] && !ft_isspace(s[i]))
				i++;
		}
		while (ft_isspace(s[i]))
			i++;
	}
	return (ret);
}

char	**malloc_strs(char *s)
{
	int		num_of_strs;
	char	**ret;

	num_of_strs = cnt_strs(s);
	ret = malloc(sizeof(char *) * (num_of_strs + 1));
	if (!ret)
		return (0);
	return (ret);
}

void	free_strs(char **ret, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(ret[j]);
	free(ret);
}

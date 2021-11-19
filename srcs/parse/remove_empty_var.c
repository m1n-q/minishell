/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 04:24:59 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/19 16:48:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	count_empty_var(char **argv)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (argv[++i])
	{
		if (argv[i] == EMPTY_VAR)
			ret++;
	}
	return (ret);
}

char	**rm_empty_var(char **argv)
{
	int		i;
	int		j;
	int		argc;
	char	**ret;

	argc = get_argc(argv) - count_empty_var(argv);
	if (argc == get_argc(argv))
		return (argv);
	ret = calloc_(argc + 1, sizeof(char **));
	i = -1;
	j = 0;
	while (++i < argc)
	{
		while (argv[j] == EMPTY_VAR)
			j++;
		if (is_token(argv[j]))
			ret[i] = argv[j++];
		else if (!is_token(argv[j]))
			ret[i] = strdup_(argv[j++]);
	}
	ret[i] = 0;
	free_till(get_argc(argv), argv);
	free(argv);
	return (ret);
}

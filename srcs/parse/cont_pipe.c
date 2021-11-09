/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:08:37 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/09 16:00:05 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

char	**join_argvs(char **argv, char **tmp)
{
	int		i;
	int		j;
	char	**ret;

	ret = malloc(sizeof(char *) * (get_argc(argv) + get_argc(tmp) + 1));
	i = -1;
	while (argv[++i])
	{
		if (argv[i] > (char *)7LL)
			ret[i] = ft_strdup(argv[i]);
		else
			ret[i] = argv[i];
	}
	j = -1;
	while (tmp[++j])
	{
		if (tmp[j] > (char *)7LL)
			ret[i++] = ft_strdup(tmp[j]);
		else
			ret[i++] = tmp[j];
	}
	ret[i] = 0;
	return (ret);
}

char	**copy_after_pipe(char **argv, char *s)
{
	char	**ret;
	char	**tmp;

	tmp = parse(s);
	if (tmp <= (char **)4LL)
		return (tmp);
	ret = join_argvs(argv, tmp);
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(tmp), tmp);
	free(tmp);
	return (ret);
}

char	**cont_pipe(char **argv)
{
	int		i;
	int		len;
	char	*line;
	char	**ret;

	i = -1;
	len = get_argc(argv);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (syntax_error((char **)UNEXPECTED_EOF, 0, EX_USAGE));
		if (!line[0])
			continue ;
		if (line)
			break ;
	}
	ret = copy_after_pipe(argv, line);
	return (ret);
}

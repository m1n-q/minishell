/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:08:37 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 14:26:49 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* join the new line argv with the previous line argv */
char	**join_argvs(char **argv, char **tmp)
{
	int		i;
	int		j;
	int		argc;
	char	**ret;

	i = -1;
	j = -1;
	argc = get_argc(argv) + get_argc(tmp);
	ret = (char **)calloc_(argc + 1, sizeof(char *));
	while (argv[++i])
	{
		if (is_token(argv[i]) == 0)
			ret[i] = strdup_(argv[i]);
		else
			ret[i] = argv[i];
	}
	while (tmp[++j])
	{
		if (is_token(tmp[j]) == 0)
			ret[i++] = strdup_(tmp[j]);
		else
			ret[i++] = tmp[j];
	}
	ret[i] = 0;
	return (ret);
}

/* get an argv of args on a new line */
char	**copy_after_pipe(char **argv, char *s)
{
	char	**tmp;
	char	**ret;

	tmp = parse(s);
	if (tmp <= UNEXPECTED_EOF)
		return (tmp);
	ret = join_argvs(argv, tmp);
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(tmp), tmp);
	free(tmp);
	return (ret);
}

/* when an arg is followed by a pipe and then a new line */
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
		{
			free_till(get_argc(argv), argv);
			free(argv);
			return (syntax_error(UNEXPECTED_EOF, 0, EX_USAGE));
		}
		if (!line[0])
			continue ;
		if (line)
			break ;
	}
	ret = copy_after_pipe(argv, line);
	return (ret);
}

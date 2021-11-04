/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:08:37 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/04 20:39:02 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

char	**cont_pipe(char **argv)
{
	int		i;
	int		len;
	char	*line;
	char	**ret;

	i = -1;
	len = get_argc(argv);
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (0);
	line = readline("> ");
	if (!line)
		return (syntax_error((char **)UNEXPECTED_EOF, 0, EX_USAGE));
	while (argv[++i])
		ret[i] = argv[i];
	ret[i++] = line;
	ret[i] = 0;
	free(argv);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:00:51 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 22:28:21 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if any of the quotes don't have a match return 0, otherwise return 1 */
int	quotes_match(char *s)
{
	int		cnt_q;
	char	c;
	char	*tofree;

	cnt_q = 0;
	tofree = s;
	while (*s)
	{
		if (is_q(*s))
		{
			c = *s++;
			cnt_q++;
			while (*s && *s != c)
				s++;
			if (!*s)
				break ;
			if (*s++ == c)
				cnt_q--;
		}
		else
			s++;
	}
	if (cnt_q)
		free(tofree);
	return (-1 + cnt_q);
}

char	*adjust_input(char *s)
{
	s = split_pipe_redir(s);
	s = rm_empty_q(s);
	return (s);
}

char	**ft_split_space(char *s)
{
	int		i;
	int		argc;
	char	*tofree;
	char	**ret;

	if (!quotes_match(s))
		return (Q_ERR);
	s = adjust_input(s);
	argc = 0;
	ret = malloc_strs(s, &argc);
	i = 0;
	tofree = s;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			ret = copy_arg(s, ret, &i, argc);
			if (ret == AMBIG_REDIR)
				break ;
			s += cnt_str_len(s) - 1;
		}
		s++;
	}
	free(tofree);
	return (ret);
}

char	**parse(char *s)
{
	int		last;
	char	**ret;

	ret = ft_split_space(s);
	if (ret == Q_ERR)
		return (syntax_error(Q_ERR, 0, EXECUTION_FAILURE));
	else if (ret == AMBIG_REDIR)
		return (ret);
	last = get_argc(ret) - 1;
	if (find_token_error(ret) != -1)
		return (token_error(ret));
	if (last > 0 && ret[last] == PIPE)
		ret = cont_pipe(ret);
	return (ret);
}

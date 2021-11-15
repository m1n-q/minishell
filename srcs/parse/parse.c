/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:00:51 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/13 17:56:07 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if the numbers of each of the quotes are odd (mismatch) return 0,
 * otherwise return 1 */
int	quotes_match(char *s)
{
	char	c;
	int		cnt_q;
	char	*tofree;

	tofree = s;
	cnt_q = 0;
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

char	**ft_split_space(char *s)
{
	int		i;
	char	**ret;
	char	*tofree;

	if (!quotes_match(s))
		return ((char **)Q_ERR);
	s = split_pipe_redir(s);
	s = rm_empty_q(s);
	ret = malloc_strs(s);
	i = 0;
	tofree = s;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			ret = cpy_str(s, ret, &i);
			if (ret == (char **)AMBIG_REDIR)
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
	char	**ret;
	int		last;

	ret = ft_split_space(s);
	if (ret == (char **)Q_ERR)
		return (syntax_error((char **)Q_ERR, 0, EXECUTION_FAILURE));
	if (ret == (char **)AMBIG_REDIR)
		return (ret);
	last = get_argc(ret) - 1;
	if (find_token_error(ret) != -1)
		return (token_error(ret));
	if (ret[last] == (char *)PIPE && last != 0)
		ret = cont_pipe(ret);
	return (ret);
}

/*	if (is_double_pipe_err(ret))
		return (syntax_error((char **)PIPE_ERR, "`||'", EX_USAGE, ret));
	if (is_pipe_err(ret, last) == 1)
		return (syntax_error((char **)PIPE_ERR, "`|'", EX_USAGE, ret));
	else if (is_pipe_err(ret, last) == 2)
		return (syntax_error((char **)PIPE_ERR, "`newline'", EX_USAGE, ret));
	if (is_redir_err(ret, last))
		return (return_redir_err(is_redir_err(ret, last), ret));*/

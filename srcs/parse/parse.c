/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:00:51 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/09 17:56:12 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if the numbers of each of the quotes are odd (mismatch) return 0,
 * otherwise return 1 */
int	quotes_match(char *s)
{
	char	c;
	int		cnt_q;

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
		return (0);
	return (1);
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
	int		str_len;
	char	**ret;
	char	*tofree;

	if (!quotes_match(s))
		return ((char **)Q_ERR);
	s = adjust_input(s);
	ret = malloc_strs(s);
	i = 0;
	str_len = 0;
	tofree = s;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			ret[i] = cpy_str(s, ret, i);
			s += cnt_str_len(s) - 1;
			i++;
		}
		s++;
	}
	ret[i] = 0;
	free(tofree);
	return (ret);
}

char	**parse(char *s)
{
	char	**ret;
	int		i;

	ret = ft_split_space(s);
	if (ret == (char **)Q_ERR)
		return (syntax_error((char **)Q_ERR, 0, EXECUTION_FAILURE));
	i = get_argc(ret) - 1;
	if (is_double_pipe_err(ret))
		return (syntax_error((char **)PIPE_ERR, "`||'", EX_USAGE));
	if (is_pipe_err(ret, i) == 1)
		return (syntax_error((char **)PIPE_ERR, "`|'", EX_USAGE));
	else if (is_pipe_err(ret, i) == 2)
		return (syntax_error((char **)PIPE_ERR, "`newline'", EX_USAGE));
	if (is_redir_err(ret, i))
		return (return_redir_err(is_redir_err(ret, i)));
	if (ret[i] == (char *)PIPE && i != 0)
		ret = cont_pipe(ret);
	return (ret);
}

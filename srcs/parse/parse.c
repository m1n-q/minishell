/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:00:51 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/04 20:57:29 by kyumlee          ###   ########.fr       */
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

char	**ft_split_space(char *s)
{
	int		i;
	int		str_len;
	char	**ret;

	if (!quotes_match(s))
		return ((char **)Q_ERR);
	s = rm_empty_q(s);
	s = split_pipe_redir(s);
	s = add_q_to_heredoc_del(s);
	ret = malloc_strs(s);
	i = 0;
	str_len = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			str_len = cnt_str_len(s);
			ret[i] = cpy_str(s, ret, &i);
			s += str_len - 1;
		}
		s++;
	}
	ret[i] = 0;
	return (ret);
}

char	**parse(char *s)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_split_space(s);
	if (ret == (char **)Q_ERR)
		return (syntax_error((char **)Q_ERR, 0, EXECUTION_FAILURE));
	if (is_double_pipe_err(ret))
		return (syntax_error((char **)PIPE_ERR, "`||'", EX_USAGE));
	while (ret[i + 1])
		i++;
	if (is_pipe_err(ret, i) == 1)
		return (syntax_error((char **)PIPE_ERR, "`|'", EX_USAGE));
	else if (is_pipe_err(ret, i) == 2)
		return (syntax_error((char **)PIPE_ERR, "`newline'", EX_USAGE));
	if (ret[i] > (char *)PIPE && ret[i] <= (char *)REDIRECT_APPEND)
		return (redir_err(ret, i));
	if (ret[i] == (char *)PIPE && i != 0)
		ret = cont_pipe(ret);
	return (ret);
}

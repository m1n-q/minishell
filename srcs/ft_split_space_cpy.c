/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_cpy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 00:03:07 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/17 17:29:50 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

char	*cpy_wo_q(char *s, char *ret);

/* trim q marks if they are within a string */
char	*trim_q(char *s)
{
	int		i;
	char	c;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(s) - 2 + 1));
	if (!ret)
		return (0);
	i = 0;
	while (*s)
	{
		if (is_q(*s))
		{
			c = *s++;
			while (*s && *s != c)
				ret[i++] = *s++;
		}
		else
			ret[i++] = *s++;
	}
	ret[i] = 0;
	return (ret);
}

/* check if there are q marks within a string */
int	has_q(char *s)
{
	while (*s)
	{
		if (is_q(*s))
			return (1);
		s++;
	}
	return (0);
}

/* copy a string that is enclosed by q marks from (s) to (ret) */
char	*cpy_with_q(char *s, char *ret)
{
	char	c;
	int		i;

	i = 0;
	while (is_q(*s) && *s && *(s + 1) && *s == *(s + 1))
		s += 2;
	if (*s && !is_q(*s))
		return (cpy_wo_q(s, ret));
	else if (*s && is_q(*s))
	{
		c = *s++;
		while (*s != c)
			ret[i++] = *s++;
		while (*++s && !ft_isspace(*s))
			ret[i++] = *s;
	}
	ret[i] = 0;
	return (ret);
}

/* copy a string that is not enclosed by q marks from (s) to (ret) */
char	*cpy_wo_q(char *s, char *ret)
{
	char	c;
	int		i;

	i = 0;
	while (*s)
	{
		ret[i++] = *s++;
		while (*s && *(s + 1) && *s == *(s + 1))
			s += 2;
		if (*s && is_q(*s))
		{
			c = *s++;
			ret[i++] = c;
			while (*s && *s != c)
				ret[i++] = *s++;
			ret[i++] = *s++;
		}
		if (ft_isspace(*s))
			break ;
	}
	ret[i] = 0;
	if (has_q(ret))
		ret = trim_q(ret);
	return (ret);
}

/* copy a string from (s) to (ret) */
char	*cpy_str(char *s, char *ret)
{
	if (is_q(*s))
		return (cpy_with_q(s, ret));
	else
		return (cpy_wo_q(s, ret));
}

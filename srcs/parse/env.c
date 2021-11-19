/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/20 00:33:03 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* count spaces in arg */
int	count_space_in_env(char *s, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (c == '"')
		return (ret);
	while (s[i] && ft_isspace(s[i++]))
		ret++;
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			while (ft_isspace(s[i]))
			{
				ret++;
				i++;
			}
			if (s[i])
				ret--;
		}
		else
			i++;
	}
	return (ret);
}

/* remove all spaces in arg except for one space
 * that divides the arguments */
char	*trim_space_in_env(char *s, char c)
{
	int		i;
	int		cnt;
	char	*ret;

	i = 0;
	cnt = count_space_in_env(s, c);
	if (!cnt)
		return (s);
	ret = calloc_(ft_strlen(s) - cnt + 1, sizeof(char));
	while (ft_isspace(*s))
		s++;
	while (*s)
	{
		if (!ft_isspace(*s))
			ret[i++] = *s++;
		else
		{
			while (ft_isspace(*s))
				s++;
			if (*s)
				ret[i++] = ' ';
		}
	}
	ret[i] = 0;
	return (ret);
}

/* if an arg is enclosed by double quotes, expand arg */
int	expand(char *s, char **p_arg, char *prev_arg)
{
	int		i;
	char	c;

	i = 0;
	c = s[i++];
	while (s[i] && s[i] != c)
	{
		if (s[i] != '$')
			i += join_non_env(&s[i], p_arg);
		if (s[i] == '$' && s[i + 1] && s[i + 1] != '?')
			i += join_env(&s[i], p_arg, prev_arg, c);
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
			i += join_exit_code(p_arg);
		else if (s[i] == '$' && s[i + 1] == c)
			i += join_dollar_at_end(p_arg);
	}
	if (!s[i])
		return (i);
	return (++i);
}

/* if an arg is enclosed by single quotes, do not expand */
int	not_expand(char *s, char **p_arg)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	c = *s++;
	while (s[i] != c)
		i++;
	tmp = calloc_n_lcpy(s, i + 1);
	if (*p_arg)
	{
		if (*p_arg != EMPTY_VAR)
			*p_arg = join_and_free(*p_arg, tmp, 3);
		else if (*p_arg == EMPTY_VAR)
			*p_arg = dup_and_free(tmp);
	}
	else if (!*p_arg)
		*p_arg = dup_and_free(tmp);
	i++;
	return (++i);
}

/* if an arg has a dollar-sign */
char	*case_env(char *s, char *arg, char **argv, int i)
{
	char	*ret;
	char	*prev_arg;

	ret = 0;
	if (i > 0)
		prev_arg = argv[i - 1];
	free(arg);
	while (*s && !ft_isspace(*s))
	{
		if (*s == '"')
			s += expand(s, &ret, prev_arg);
		else if (*s == '\'')
			s += not_expand(s, &ret);
		else if (*s != '$')
			s += join_non_env(s, &ret);
		else if (*s == '$' && *(s + 1) && *(s + 1) != '?')
			s += join_env(s, &ret, prev_arg, 0);
		else if (*s == '$' && *(s + 1) && *(s + 1) == '?')
			s += join_exit_code(&ret);
		else if (*s == '$' && !*(s + 1))
			s += join_dollar_at_end(&ret);
		if (ret == (char *)AMBIG_REDIR)
			return ((char *)AMBIG_REDIR);
	}
	return (ret);
}

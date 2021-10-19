/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:10 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/20 00:47:56 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	is_env(char c)
{
	return (ft_isdigit(c) || (c >= 'A' && c <= 'Z') || c == '_');
}

char	*join_char(char *s, char c)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!ret)
		return (0);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i++] = c;
	ret[i] = 0;
	return (ret);
}

int	join_env_val(char *s, char **ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while (is_env(s[i]))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, s, i + 1);
	if (*ret)
		*ret = ft_strjoin(*ret, getenv(tmp));
	else
		*ret = getenv(tmp);
	free(tmp);
	i++;
	return (i);
}

int	join_rest(char *s, char **ret)
{
	int	i;

	i = 0;
	while (s[i] && !is_env(s[i]) && s[i] != '$')
	{
		*ret = join_char(*ret, s[i]);
		i++;
	}
	return (i);
}

char	*case_env(char *s)
{
	char	*ret;

	ret = 0;
	while (*s)
	{
		if (*s && *(s + 1) && *s == '$' && !ft_isspace(*(s + 1)))
			s += join_env_val(s + 1, &ret);
		if (!*s || ft_isspace(*s))
			break ;
		else
			s += join_rest(s, &ret);
	}
	return (ret);
}

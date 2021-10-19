/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:24:10 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/19 17:43:34 by kyumlee          ###   ########.fr       */
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

char	*join_env_val(char *s, char *ret, int *i)
{
	int		j;
	int		len;
	char	*tmp;

	j = ++(*i);
	len = 0;
	while (is_env(s[*i]) && len++)
		(*i)++;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, &s[j], len + 1);
	if (ret)
		ret = ft_strjoin(ret, getenv(tmp));
	else
		ret = getenv(tmp);
	*i += len;
	free(tmp);
	return (ret);
}

char	*join_rest(char *s, char *ret, int *i)
{
	while (s[*i] && !is_env(s[*i]))
	{
		ret = join_char(ret, s[*i]);
		(*i)++;
	}
	return (ret);
}

char	*case_env(char *s)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$')
			ret = join_env_val(s, ret, &i);
		else
			ret = join_rest(s, ret, &i);
		if (ft_isspace(s[i]))
			break ;
	}
	return (ret);
}

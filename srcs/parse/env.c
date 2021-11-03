/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/04 04:27:48 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if a character is an available character for enviroment variable */
int	join_exit_code(char **ret)
{
	if (!*ret)
		*ret = ft_itoa(get_or_set_exitcode(GET, 0));
	else if (*ret)
		*ret = ft_strjoin(*ret, ft_itoa(get_or_set_exitcode(GET, 0)));
	return (2);
}

int	join_dollar_sign(char *s, char **ret)
{
	int		i;
	int		cnt;
	char	*tmp;

	i = -1;
	cnt = 0;
	while (s[++i] == '$')
		cnt++;
	if (s[i] && !ft_isspace(s[i]) && s[i] != '"' && cnt > 2)
		cnt--;
	tmp = malloc(sizeof(char) * (cnt + 1));
	i = -1;
	while (++i < cnt)
		tmp[i] = '$';
	tmp[i] = 0;
	*ret = ft_strjoin(*ret, tmp);
	return (cnt);
}

/* join the value of the environment variables */
int	join_env_var(char *s, char **ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		i++;
	if (!i)
		return (join_dollar_sign(s, ret));
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, &s[1], i + 1);
	if (!*ret)
		*ret = getenv(tmp);
	else if (*ret)
		*ret = ft_strjoin(*ret, getenv(tmp));
	else if (*ret)
		*ret = ft_strjoin(*ret, getenv(*ret));
	if (!*ret)
	{
		*ret = malloc(sizeof(char) * 1);
		if (!*ret)
			return (0);
		*ret[0] = 0;
	}
	return (++i);
}

int	join_non_env(char *s, char **ret)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] && s[i] != '$' && s[i] != '"')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(tmp, s, i + 1);
	if (*ret)
		*ret = ft_strjoin(*ret, tmp);
	else
		*ret = tmp;
	return (i);
}

/* if the first letter is a dollar-sign or 
 * a double quotation mark followed by a dollar sign
 */
char	*case_env(char *s, char tok)
{
	char	*ret;

	ret = 0;
	while (*s && *s != tok)
	{
		if (*s != '$')
			s += join_non_env(s, &ret);
		else if (*s == '$' && *(s + 1) && *(s + 1) != '?')
			s += join_env_var(s, &ret);
		else if (*s == '$' && *(s + 1) && *(s + 1) == '?')
			s += join_exit_code(&ret);
	}
	return (ret);
}

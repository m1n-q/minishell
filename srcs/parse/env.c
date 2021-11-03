/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/03 14:46:17 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if a character is an available character for enviroment variable */
int	is_env(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || c == '_');
}

int	join_exit_code(char **ret)
{
	if (!*ret)
		*ret = ft_itoa(get_or_set_exitcode(GET, 0));
	else if (*ret)
		*ret = ft_strjoin(*ret, ft_itoa(get_or_set_exitcode(GET, 0)));
	return (2);
}

/* join the value of the environment variables */
int	join_env_var(char *s, char **ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while (is_env(s[i + 1]))
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, &s[1], i + 1);
	if (!*ret)
		*ret = getenv(tmp);
	else if (*ret)
		*ret = ft_strjoin(*ret, getenv(tmp));
	if (!*ret)
	{
		*ret = malloc(sizeof(char) * 1);
		if (!*ret)
			return (0);
		*ret[0] = 0;
	}
	free(tmp);
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
char	*case_env(char *s)
{
	char	*ret;

	ret = 0;
	while (*s)
	{
		if (*s == '"')
			s++;
		if (*s != '$')
			s += join_non_env(s, &ret);
		else if (*s == '$' && *(s + 1) && *(s + 1) != '?')
			s += join_env_var(s, &ret);
		else if (*s == '$' && *(s + 1) && *(s + 1) == '?')
			s += join_exit_code(&ret);
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 13:00:44 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if a character is an available character for enviroment variable */
int	join_exit_code(char **p_arg)
{
	if (!*p_arg)
		*p_arg = ft_itoa(get_or_set_exitcode(GET, 0));
	else if (*p_arg)
		*p_arg = join_and_free(*p_arg, ft_itoa(get_or_set_exitcode(GET, 0)), 2);
	return (2);
}

int	join_dollar_sign(char *s, char **p_arg)
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
	tmp = (char *)ft_calloc(cnt + 1, sizeof(char));
	i = -1;
	while (++i < cnt)
		tmp[i] = '$';
	tmp[i] = 0;
	*p_arg = join_and_free(*p_arg, tmp, 3);
	return (cnt);
}

/* join the value of the environment variables */
int	join_env_var(char *s, char **p_arg)
{
	int		i;
	char	*env;

	i = 0;
	while (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		i++;
	if (!i)
		return (join_dollar_sign(s, p_arg));
	env = getenv(s + 1);
	if (env)
	{
		if (!*p_arg)
		{
			free(*p_arg);
			*p_arg = ft_strdup(env);
		}
		else if (*p_arg)
			*p_arg = join_and_free(*p_arg, env, 1);
	}
	else
		*p_arg = ft_strjoin(*p_arg, NULL);
	return (++i);
}

int	join_non_env(char *s, char **p_arg)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] && s[i] != '$' && s[i] != '"')
		i++;
	tmp = (char *)ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(tmp, s, i + 1);
	if (*p_arg)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else
		*p_arg = dup_and_free(tmp);
	if (s[i] == '$' && !s[i + 1])
	{
		*p_arg = join_and_free(*p_arg, "$", 1);
		i++;
	}
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

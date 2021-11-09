/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/09 21:38:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if a character is an available character for enviroment variable */
int	join_exit_code(char **argv)
{
	if (!*argv)
		*argv = ft_itoa(get_or_set_exitcode(GET, 0));
	else if (*argv)
		*argv = ft_strjoin(*argv, ft_itoa(get_or_set_exitcode(GET, 0)));
	return (2);
}

int	join_dollar_sign(char *s, char **argv)
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
	*argv = ft_strjoin(*argv, tmp);
	return (cnt);
}

/* join the value of the environment variables */
int	join_env_var(char *s, char **argv)
{
	int		i;
	char	*tmp;
	char	*env;

	i = 0;
	while (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		i++;
	if (!i)
		return (join_dollar_sign(s, argv));
	tmp = (char *)ft_calloc(i + 1, sizeof(char));
	if (!tmp)
		return (0);
	ft_strlcpy(tmp, &s[1], i + 1);
	env = getenv(tmp);
	if (env)
	{
		if (!*argv)
			*argv = ft_strdup(env);
		else if (*argv)
			*argv = ft_strjoin(*argv, env);
	}
	else
		*argv = ft_strjoin(*argv, NULL);
	free(tmp);
	return (++i);
}

int	join_non_env(char *s, char **argv)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] && s[i] != '$' && s[i] != '"')
		i++;
	tmp = (char *)ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(tmp, s, i + 1);
	if (*argv)
		*argv = ft_strjoin(*argv, tmp);
	else
		*argv = tmp;
	if (s[i] == '$' && !s[i + 1])
	{
		*argv = ft_strjoin(*argv, "$");
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

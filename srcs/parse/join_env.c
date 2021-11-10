/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 20:31:45 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* get the exit code */
int	join_exit_code(char **p_arg)
{
	if (!*p_arg)
		*p_arg = itoa_(get_or_set_exitcode(GET, 0)); //LEAK
	else if (*p_arg)
		*p_arg = join_and_free(*p_arg, itoa_(get_or_set_exitcode(GET, 0)), 2);
	return (2);
}

/* if a dollar sign is followed by dollar signs */
int	join_dollar_sign(char *s, char **p_arg)
{
	int		i;
	int		cnt;
	char	*tmp;

	i = -1;
	cnt = 0;
	while (s[++i] && !ft_isdigit(s[i]) && !ft_isalpha(s[i]) && s[i] != '_')
		cnt++;
	if (cnt % 2 && cnt > 0)
		cnt--;
	tmp = calloc_n_lcpy(s, cnt + 1);
	*p_arg = join_and_free(*p_arg, tmp, 3);
	return (cnt);
}

/* join the value of the environment variables */
int	join_env_var(char *s, char **p_arg)
{
	int		i;
	char	*env;
	char	*tmp;

	i = 0;
	while (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		i++;
	if (!i)
		return (join_dollar_sign(s, p_arg));
	tmp = calloc_n_lcpy(s + 1, i + 1);
	env = getenv(tmp);
	free(tmp);
	if (env)
	{
		if (!*p_arg)
		{
			free(*p_arg);
			*p_arg = strdup_(env);
		}
		else if (*p_arg)
			*p_arg = join_and_free(*p_arg, env, 1);
	}
	else
		*p_arg = strjoin_(*p_arg, NULL);
	return (++i);
}

int	join_non_env(char *s, char **p_arg)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] && s[i] != '$' && !is_q(s[i]))
		i++;
	tmp = calloc_n_lcpy(s, i + 1);
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

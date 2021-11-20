/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:22 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/20 22:17:14 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if <, >, or << is followed by notexisting_env_var */
char	*ambig_redir_err(char *tmp)
{
	get_or_set_exitcode(SET, 1);
	ft_putstr_fd("minishell: $", STDERR_FILENO);
	ft_putstr_fd(tmp, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	return ((char *)AMBIG_REDIR);
}

void	join_wo_q(char **p_arg, char *env)
{
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, env, 1);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = strdup_(env);
	else if (!*p_arg)
	{
		free(*p_arg);
		if (*env)
			*p_arg = strdup_(env);
		else
			*p_arg = EMPTY_VAR;
	}
}

void	join_with_q(char **p_arg, char *env)
{
	char	*tmp;

	tmp = joinjoin("\"", env, "\"");
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = dup_and_free(tmp);
	else if (!*p_arg)
		*p_arg = dup_and_free(tmp);
}

/* join the env_var_value with arg */
void	join_env_var(char *env, char **p_arg, char c)
{
	if (env == EMPTY_VAR)
	{
		if (!*p_arg)
			*p_arg = env;
		return ;
	}
	if (c == '"')
		join_with_q(p_arg, env);
	else if (c != '"')
		join_wo_q(p_arg, env);
}

/* join env_var_value */
int	join_env(char *s, char **p_arg, char *prev_arg, char c)
{
	int		i;
	char	*tmp;
	char	*env;

	i = 0;
	while (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		i++;
	if (!i)
		return (join_dollar_sign(s, p_arg));
	tmp = calloc_n_lcpy(s + 1, i + 1);
	env = getenv(tmp);
	if (env)
		join_env_var(env, p_arg, c);
	else if (!env)
	{
		if (is_redir_token(prev_arg))
			*p_arg = ambig_redir_err(tmp);
		else
			join_env_var(EMPTY_VAR, p_arg, c);
	}
	free(tmp);
	return (++i);
}

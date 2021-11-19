/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:22 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/19 17:04:47 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* join exit_code with arg */
/*int	join_exit_code(char **p_arg)
{
	char	*tmp;

	tmp = itoa_(get_or_set_exitcode(GET, 0));
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = dup_and_free(tmp);
	else if (!*p_arg)
		*p_arg = dup_and_free(tmp);
	return (2);
}*/

/* join other signs that are followed by a dollar-sign */
/*int	join_dollar_sign(char *s, char **p_arg)
{
	int		i;
	int		cnt;
	char	*tmp;

	i = -1;
	cnt = 0;
	while (s[++i] && s[i] != '"' && s[i] != '_'
		&& !ft_isdigit(s[i]) && !ft_isalpha(s[i]) && s[i] != '_')
		cnt++;
	if (cnt % 2 && cnt > 0 && s[i] != '"')
		cnt--;
	tmp = calloc_n_lcpy(s, cnt + 1);
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = dup_and_free(tmp);
	else if (!*p_arg)
		*p_arg = dup_and_free(tmp);
	if (s[i] == '"')
		cnt++;
	return (cnt);
}*/

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

	tmp = strdup_("\"");
	tmp = join_and_free(tmp, env, 1);
	tmp = join_and_free(tmp, "\"", 1);
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = strdup_(env);
	else if (!*p_arg)
		*p_arg = strdup_(env);
}

/* join the env_var_value with arg */
void	join_env_var(char *env, char **p_arg, char c)
{
	char	*new;

	if (env == EMPTY_VAR)
	{
		if (!*p_arg)
			*p_arg = env;
		return ;
	}
	new = trim_space_in_env(env, c);
	if (c == '"')
		join_with_q(p_arg, new);
	else if (c != '"')
		join_wo_q(p_arg, new);
	if (!is_equal(new, env))
		free(new);
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
	if (c == '"')
		i++;
	return (++i);
}

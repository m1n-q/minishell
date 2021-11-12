/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:36:22 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/12 18:50:58 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	join_exit_code(char **p_arg)
{
	if (!*p_arg)
		*p_arg = itoa_(get_or_set_exitcode(GET, 0));
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

char	**ambig_redir_err(char *tmp)
{
	get_or_set_exitcode(SET, 1);
	ft_putstr_fd("minishell: $", STDERR_FILENO);
	ft_putstr_fd(tmp, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	return ((char **)AMBIG_REDIR);
}

void	join_env_var(char *env, char **p_arg, char c)
{
	char	*new;

	new = trim_space_in_env(env, c);
	if (!*p_arg)
	{
		free(*p_arg);
		*p_arg = strdup_(new);
	}
	else if (*p_arg)
		*p_arg = join_and_free(*p_arg, new, 1);
	if (!is_equal(new, env))
		free(new);
}

/* join the value of the environment variables */
int	join_env(char *s, char **p_arg, char ***argv, int j)
{
	int		i;
	int		alloc_check;
	char	*env;
	char	*tmp;
	char	c;

	i = 0;
	alloc_check = 0;
	c = *s++;
	while (ft_isdigit(s[i + 1]) || ft_isalpha(s[i + 1]) || s[i + 1] == '_')
		i++;
	if (!i)
		return (join_dollar_sign(s, p_arg));
	tmp = calloc_n_lcpy(s + 1, i + 1);
	env = getenv(tmp);
	if (env)
		join_env_var(env, p_arg, c);
	else if (!env && j >= 0 && \
		*argv[j] >= (char *)5LL && *argv[j] <= (char *)7LL)
		*argv = ambig_redir_err(tmp);
	free(tmp);
	return (++i);
}

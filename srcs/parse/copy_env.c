/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 21:28:30 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 15:53:26 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	copy_non_env(char *arg, char **new_arg)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i] && arg[i] != '$' && !is_q(arg[i]))
		i++;
	tmp = calloc_n_lcpy(arg, i + 1);
	if (*new_arg)
		*new_arg = join_and_free(*new_arg, tmp, 3);
	else
		*new_arg = dup_and_free(tmp);
	return (i);
}

int	copy_exit_code(char **new_arg)
{
	char	*tmp;

	tmp = itoa_(get_or_set_exitcode(GET, 0));
	if (*new_arg)
		*new_arg = join_and_free(*new_arg, tmp, 3);
	else
		*new_arg = dup_and_free(tmp);
	return (2);
}

int	copy_other_signs(char *arg, char **new_arg)
{
	int		i;
	char	*tmp;
	char	*signs;

	i = 0;
	while (arg[i] && arg[i] != '"'
		&& !ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && arg[i] != '_')
		i++;
	if (i > 0 && !(i % 2))
		i--;
	tmp = strdup_("$");
	signs = calloc_n_lcpy(arg, i + 1);
	tmp = join_and_free(tmp, signs, 3);
	if (*new_arg)
		*new_arg = join_and_free(*new_arg, tmp, 3);
	else
		*new_arg = dup_and_free(tmp);
	return (i + 1);
}

int	copy_others(char *arg, char **new_arg)
{
	if (!*arg)
	{
		*new_arg = join_and_free(*new_arg, "$", 1);
		return (1);
	}
	if (*arg == '?')
		return (copy_exit_code(new_arg));
	else
		return (copy_other_signs(arg, new_arg));
	return (0);
}

int	copy_env_val(char *arg, char **new_arg, char *prev_arg, char q)
{
	int		i;
	char	*env_name;
	char	*env_val;

	arg++;
	i = 0;
	while (ft_isdigit(arg[i]) || ft_isalpha(arg[i]) || arg[i] == '_')
		i++;
	if (!i)
		return (copy_others(arg, new_arg));
	env_name = calloc_n_lcpy(arg, i + 1);
	env_val = getenv(env_name);
	free(env_name);
	if (*new_arg)
		*new_arg = join_and_free(*new_arg, env_val, 1);
	else
		*new_arg = strdup_(env_val);
	if (is_redir_token(prev_arg) && prev_arg != HEREDOC
		&& (!env_val || (env_has_space(env_val, '$') && q != '"' )))
	{
		free(*new_arg);
		*new_arg = (char *)AMBIG_REDIR;
	}
	return (++i);
}

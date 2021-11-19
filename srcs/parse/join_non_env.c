/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_non_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:08 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/19 17:06:33 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* join all non_env_value to arg */
int	join_non_env(char *s, char **p_arg)
{
	char	*tmp;
	int		i;

	i = 0;
	if (s[i] == '\'')
		i++;
	while (s[i] && s[i] != '$' && !is_q(s[i]))
		i++;
	tmp = calloc_n_lcpy(s, i + 1);
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = dup_and_free(tmp);
	else if (!*p_arg)
		*p_arg = dup_and_free(tmp);
	return (i);
}

/* join exit_code with arg */
int	join_exit_code(char **p_arg)
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
}

/* join other signs that are followed by a dollar-sign */
int	join_dollar_sign(char *s, char **p_arg)
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
}

/* join one dollar-sign at the end */
int	join_dollar_at_end(char **p_arg)
{
	if (*p_arg && *p_arg != EMPTY_VAR)
		*p_arg = join_and_free(*p_arg, "$", 1);
	else if (*p_arg && *p_arg == EMPTY_VAR)
		*p_arg = strdup_("$");
	else if (!*p_arg)
		*p_arg = strdup_("$");
	return (1);
}

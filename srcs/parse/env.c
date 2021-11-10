/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:33:01 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/10 16:57:23 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	expand(char *s, char **p_arg)
{
	int		i;
	char	c;

	i = 0;
	c = s[i++];
	while (s[i] != c)
	{
		if (s[i] != '$')
			i += join_non_env(&s[i], p_arg);
		if (s[i] == '$' && s[i + 1] && s[i + 1] != '?')
			i += join_env_var(&s[i], p_arg);
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
			i += join_exit_code(p_arg);
	}
	return (++i);
}

int	not_expand(char *s, char **p_arg)
{
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	c = *s++;
	while (s[i] != c)
		i++;
	tmp = calloc_n_lcpy(s, i + 1);
	if (*p_arg)
		*p_arg = join_and_free(*p_arg, tmp, 3);
	else
		*p_arg = tmp;
	i++;
	return (++i);
}

/* if the first letter is a dollar-sign or
 * a double quotation mark followed by a dollar sign */
char	*case_env(char *s, char *arg)
{
	char	*ret;

	ret = 0;
	free(arg);
	while (*s && !ft_isspace(*s))
	{
		if (*s == '"')
			s += expand(s, &ret);
		if (*s == '\'')
			s += not_expand(s, &ret);
		if (*s != '$')
			s += join_non_env(s, &ret);
		if (*s == '$' && *(s + 1) && *(s + 1) != '?')
			s += join_env_var(s, &ret);
		else if (*s == '$' && *(s + 1) && *(s + 1) == '?')
			s += join_exit_code(&ret);
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:10:04 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 15:11:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* check if an arg has a dollar-sign */
int	expand(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			c = s[i];
			while (s[++i] != c)
				;
		}
		else if (s[i] == '"')
		{
			c = s[i];
			while (s[++i] != c)
				if (s[i] == '$')
					return (i);
		}
		else if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	has_quotes(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))
			return (1);
	}
	return (0);
}

int	count_env(char *arg)
{
	char	c;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	c = arg[i];
	while (arg[++i] != c)
	{
		if (arg[i] == '$')
			ret++;
	}
	return (ret);
}

/* if <, >, or << is followed by notexisting_env_var */
char	*ambiguous_redirect_error(char *arg)
{
	get_or_set_exitcode(SET, 1);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	return ((char *)AMBIG_REDIR);
}

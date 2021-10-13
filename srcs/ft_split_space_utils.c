/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyumlee <kyumlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:48:56 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/13 19:52:13 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"
#include "./../incs/libft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
			|| c == '\n' || c == '\v' || c == '\f');
}

int	cnt_s(char const *s)
{
	int	ret;

	ret = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isspace(*s) && (ft_isspace(*(s + 1)) || !*(s + 1)))
			ret++;
		s++;
	}
	return (ret);
}

int	cnt_d_q(char *s, int ret, t_cmd *cmd)
{
	cmd->d_q++;
	ret++;
	while (*(++s))
	{
		ret++;
		if (*s == '"')
		{
			cmd->d_q--;
			break ;
		}
	}
	return (ret);
}

int	cnt_s_q(char *s, int ret, t_cmd *cmd)
{
	cmd->s_q++;
	ret++;
	while (*(++s))
	{
		ret++;
		if (*s == '\'')
		{
			cmd->s_q--;
			break ;
		}
	}
	return (ret);
}

int	cnt_s_len(char const *s, t_cmd *cmd)
{
	int		ret;
	char	*tmp;

	tmp = (char *)s;
	ret = 0;
	while (ft_isspace(*tmp))
		tmp++;
	if (*tmp == '"')
		return (cnt_d_q(tmp, ret, cmd));
	else if (*tmp == '\'')
		return (cnt_s_q(tmp, ret, cmd));
	while (*tmp)
	{
		if (!ft_isspace(*tmp))
			ret++;
		else
			break ;
		tmp++;
	}
	return (ret);
}

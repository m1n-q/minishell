/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:12:58 by kyumlee           #+#    #+#             */
/*   Updated: 2021/10/14 17:48:20 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"
#include "./../incs/libft.h"

char	**malloc_strs(char const *s)
{
	char	**ret;

	if (!s)
		return (0);
	ret = (char **)malloc(sizeof(char *) * (cnt_s(s) + 1));
	if (!ret)
		return (0);
	return (ret);
}

void	free_strs(char **strs, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(strs[j]);
	free(strs);
}

int	cnt_q(char *s, char c)
{
	int	ret;

	ret = 0;
	while (*s++)
	{
		if (*s == c)
			ret++;
	}
	return (ret);
}

char	*del_quotes(char *s, char c)
{
	char	*tmp;
	int		i;
	int		j;

	if (!cnt_q(s, c) || cnt_q(s, c) % 2)
		return (s);
	tmp = malloc(sizeof(char) * (ft_strlen(s) + 1));
	ft_strlcpy(tmp, s, ft_strlen(s) + 1);
	i = -1;
	j = 0;
	while (tmp[++i])
	{
		if (tmp[i] != c)
			s[j++] = tmp[i];
	}
	s[j] = 0;
	return (s);
}

int	detect_q(char *s)
{
	while (*s++)
	{
		if (*s == '"')
			return (1);
		if (*s == '\'')
			return (2);
	}
	return (0);
}

char	*cpy_str(char **strs, char const *s, t_cmd *cmd, int i)
{
	strs[i] = (char *)malloc(sizeof(char) * (cnt_s_len(s, cmd) + 1));
	if (!strs[i])
	{
		free_strs(strs, i);
		return (0);
	}
	if (*s == '"' || *s == '\'')
		ft_strlcpy(strs[i], s + 1, cnt_s_len(s, cmd) - 1);
	else
		ft_strlcpy(strs[i], s, cnt_s_len(s, cmd) + 1);
	if (detect_q(strs[i]) == 1)
		del_quotes(strs[i], '"');
	else if (detect_q(strs[i]) == 2)
		del_quotes(strs[i], '\'');
	return (strs[i]);
}

char	**ft_split_space(char const *s, t_cmd *cmd)
{
	char	**ret;
	int		i;

	ret = malloc_strs(s);
	i = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			ret[i] = cpy_str(ret, s, cmd, i);
			s += cnt_s_len(s, cmd);
			i++;
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

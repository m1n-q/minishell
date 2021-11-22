/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 16:03:13 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

static size_t	count2(const char *str)
{
	size_t	count;
	char	q;

	count = 0;
	q = 0;
	while (*str)
	{
		if (*str && !ft_isspace(*str))
		{
			count++;
			while (*str && !ft_isspace(*str))
			{
				if (is_q(*str))
				{
					q = *str;
					while (*++str != q)
						;
				}
				str++;
			}
		}
		while (ft_isspace(*str))
			str++;
	}
	return (count);
}

static char	**split2(char const *s)
{
	char	**ret;
	char	q;
	size_t	count;
	size_t	arr_idx;
	size_t	i;

	if (!s)
		return (NULL);
	q = 0;
	count = count2(s);
	ret = (char **)calloc_(count + 1, sizeof(char *));
	arr_idx = 0;
	while (arr_idx < count && *s)
	{
		i = 0;
		while (ft_isspace(*s))
			s++;
		while (!ft_isspace(s[i]) && s[i])
		{
			if (is_q(s[i]))
			{
				q = s[i];
				while (s[++i] != q)
					;
			}
			i++;
		}
		ret[arr_idx] = (char *)calloc_(i + 1, sizeof(char));
		ft_strlcpy(ret[arr_idx++], s, i + 1);
		s += i;
	}
	return (ret);
}

/* split env_var_value with space and join it to the original argv, except q */
char	**split_except_quotes(char **argv, int *i, int argc, char *raw)
{
	int		j;
	int		tmp_i;
	char	**tmp;
	char	**ret;

	(void)raw;
	if (is_token(argv[*i]))
	{
		*i += 1;
		return (argv);
	}
	tmp = split2(argv[*i]);
	ret = (char **)calloc_(argc + 1, sizeof(char *));
	j = -1;
	tmp_i = -1;
	while (++j < *i)
	{
		if (is_token(argv[j]))
			ret[j] = argv[j];
		else
			ret[j] = strdup_(argv[j]);
	}
	while (++tmp_i < get_argc(tmp))
		ret[j++] = quotes_trimmer(tmp[tmp_i]);
	*i = j;
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(tmp), tmp);
	free(tmp);
	return (ret);
}

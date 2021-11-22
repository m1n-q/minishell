/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/22 17:54:41 by mishin           ###   ########.fr       */
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

static void	split_internal(char const *s, char **arr, size_t count)
{
	char	q;
	size_t	i;
	size_t	arr_idx;

	q = 0;
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
		arr[arr_idx] = (char *)calloc_(i + 1, sizeof(char));
		ft_strlcpy(arr[arr_idx++], s, i + 1);
		s += i;
	}
}

static char	**split_except_quotes(char const *s)
{
	char	**ret;
	size_t	count;

	if (!s)
		return (NULL);
	count = count2(s);
	ret = (char **)calloc_(count + 1, sizeof(char *));
	split_internal(s, ret, count);
	return (ret);
}

static void	free_sources(char **argv, char **arr)
{
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(arr), arr);
	free(arr);
}

/* split env_var_value with space and join it to the original argv, except q */
char	**split_and_trim_quotes(char **argv, int *i, int argc)
{
	int		j;
	int		tmp_i;
	char	**arr;
	char	**ret;

	if ((is_token(argv[*i]) || argv[*i] == EMPTY_VAR) && (++*i))
		return (argv);
	arr = split_except_quotes(argv[*i]);
	ret = (char **)calloc_(argc + 1, sizeof(char *));
	j = -1;
	tmp_i = -1;
	while (++j < *i)
	{
		if (is_empty(argv[j]) || is_token(argv[j]))
			ret[j] = argv[j];
		else
			ret[j] = strdup_(argv[j]);
	}
	while (++tmp_i < get_argc(arr))
		ret[j++] = quotes_trimmer(arr[tmp_i]);
	*i = j;
	free_sources(argv, arr);
	return (ret);
}

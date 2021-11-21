/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/21 23:19:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

/* if env_var_value has space */
int	env_has_space(char *s, char c)
{
	int	i;
	int	cnt_space;

	if (s == EMPTY_VAR || !s || c != '$')
		return (0);
	i = 0;
	cnt_space = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		if (ft_isspace(s[i]) && s[i + 1] && !ft_isspace(s[i + 1]))
			cnt_space++;
		i++;
	}
	return (cnt_space);
}

static size_t	count2(const char *str, size_t *arr_idx)
{
	size_t	count;
	char	q;

	*arr_idx = 0;
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
						;					// quotes 이 연속된 경우? "aaaa""a" =>두개로 나누는게 아니고 이어줘야댐
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
	count = count2(s, &arr_idx);
	ret = (char **)calloc_(count + 1, sizeof(char *));
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
					;							// quotes 이 연속된 경우? 한문자열로 붙어야댐.
			}
			i++;
		}
		ret[arr_idx] = (char *)calloc_(i + 1, sizeof(char));
		ft_strlcpy(ret[arr_idx++], s, i + 1);
		s += i;
	}
	return (ret);
}

char	*where_to_trim(char *s, int *trimcount)
{
	int		i;
	int		on_dq;
	int		on_sq;
	int		count;
	char	*trim_index;

	trim_index = (char *)calloc_(ft_strlen(s) + 1, sizeof(char));

	i = 0;
	on_sq = 0;
	on_dq = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (!on_dq && !on_sq)
				on_sq = 1;
			else
				on_sq = 0;
			if (!on_dq)
			{
				trim_index[i]++;
				count++;
			}
		}
		if (s[i] == '"')
		{
			if (!on_sq && !on_dq)
				on_dq = 1;
			else
				on_dq = 0;
			if (!on_sq)
			{
				trim_index[i]++;
				count++;
			}
		}
		i++;
	}
	*trimcount = count;
	return (trim_index);
}

static char	*quotes_trimmer(char *s)
{
	int		i;
	int		j;
	int		trimcount;
	char	*trim_index;
	char	*trimmed_string;

	trim_index = where_to_trim(s, &trimcount);
	trimmed_string = NULL;
	trimmed_string = (char *)calloc_(ft_strlen(s) - trimcount + 1, sizeof(char));
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (!trim_index[i])
			trimmed_string[j++] = s[i];
	}
	free(trim_index);
	return (trimmed_string);
}

/* split env_var_value with space and join it to the original argv, except q */
char	**split_except_quotes(char **argv, int *i, int argc, char *raw)
{
	int		j;
	int		tmp_i;
	char	**tmp;
	char	**ret;

	(void)raw;
	tmp = split2(argv[*i]);
	ret = (char **)calloc_(argc + 1, sizeof(char *));
	j = -1;
	tmp_i = -1;
	while (++j < *i)
	{
		if (is_token(argv[j]) || argv[j] == EMPTY_VAR)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:48:12 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/20 22:16:09 by kyumlee          ###   ########.fr       */
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

/* split env_var_value with space and join it to the original argv */
char	**split_and_join_till(char **argv, int *i, int argc, char *raw)
{
	int		j;
	int		tmp_i;
	// char	*raw_env;
	char	**tmp;
	char	**ret;

	(void)raw;
	// int	cut =0;

	// while (raw[cut] && !ft_isspace(raw[cut]))
	// 	cut++;

	// char *cutted;
	// cutted = calloc_n_lcpy(raw, cut + 1);
	// printf("cutted:[%s]\n", cutted);
	// int cutted_argc =0;

	// char	**expanded_list = malloc_strs(cutted, &cutted_argc);
	// printf("cutted argc=%d\n", cutted_argc);



	// int k = -1;
	// int l = 0;
	// int	dummy = 0;
	// int	minicut;
	// minicut = 0;
	// printf("cut:%d\n", cut);
	// while (++k < cut)
	// {
	// 	minicut = 0;
	// 	if (cutted[k] == '$')
	// 	{
	// 		expanded_list[l++] = getenv_(&cutted[k + 1], NULL, 0);
	// 	}
	// 	else
	// 	{
	// 		while (cutted[minicut] && !ft_isspace(cutted[minicut]))
	// 			minicut++;
	// 		expanded_list[l++] = calloc_n_lcpy(&cutted[k], minicut + 1);
	// 	}
	// 	k += count_n_skip_env(&cutted[k], cutted[k], &dummy) - 1;
	// 	printf("index k:%d\n",k);
	// }

	// int p = -1;
	// while (expanded_list[++p])
	// 	printf("expanded list[%d]=[%s]\n", p, expanded_list[p]);


	// int p = -1;

	// while (expanded_list[++p])
	// {
	// 	if (p > 0 && expanded_list[p - 1] && !has_trailing_space(expanded_list[p - 1]))
	// 		p-1 & p will not join.

	// 	if (expanded_list[p + 1] && has_leading_space(expanded_list[p + 1]))
	// 		p & p+1 will not join.
	// }









	tmp = ft_split(argv[*i], ' ');
	ret = calloc_(argc + 1, sizeof(char **));
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
		ret[j++] = strdup_(tmp[tmp_i]);
	*i = j;
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(tmp), tmp);
	free(tmp);
	return (ret);
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
				if (*str == '"')
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

char	**split2(char const *s)
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
			if (s[i] == '"')
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

char	*strdup_wo_q(const char *s1)
{
	char	*new;
	int		i;
	int		j;
	int		k;
	int		q;

	new = 0;
	i = 0;
	q = 0;
	while (s1[i])
	{
		if (s1[i] == '"')
			q++;
		i++;
	}
	new = (char *)calloc_((i - q + 1), sizeof(char));
	j = 0;
	k = 0;
	while (j < i)
	{
		if (s1[j] != '"')
			new[k++] = s1[j];
		j++;
	}
	return (new);
}

char	**just_join_with_arg(char **argv, int *i, int argc, char *raw)
{
	int		j;
	int		tmp_i;
	char	**tmp;
	char	**ret;

	(void)raw;

	tmp = split2(argv[*i]);
	ret = calloc_(argc + 1, sizeof(char **));
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
		ret[j++] = strdup_wo_q(tmp[tmp_i]);
	*i = j;
	free_till(get_argc(argv), argv);
	free(argv);
	free_till(get_argc(tmp), tmp);
	free(tmp);
	return (ret);
}

/*
	methods 1
	따옴표 안에 있는것들은 스플릿에 포함 안되게 새로운 스플릿 만들기
*/

/*
	methods 2
	따옴표안의 확장은 아예 다른 곳에서 하기
*/

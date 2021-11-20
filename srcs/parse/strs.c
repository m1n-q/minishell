/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:01:31 by kyumlee           #+#    #+#             */
/*   Updated: 2021/11/20 22:00:53 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../incs/minishell.h"

int	has_leading_space(char *s)
{
	if (!s || s == EMPTY_VAR || !*s)
		return (0);
	if (ft_isspace(s[0]))
		return (1);
	return (0);
}

int	has_trailing_space(char *s)
{
	if (!s || s == EMPTY_VAR || !*s)
		return (0);
	if (ft_isspace(s[ft_strlen(s) - 1]))
		return (1);
	return (0);
}

int	next_idx(char *s, int cur)
{
	while (ft_isalpha(s[cur]) || ft_isdigit(s[cur]) || s[cur] == '_')
		cur++;
	return (cur);
}


/* skip quotes when counting how many args there are */
int	skip_q(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[i++];
	while (s[i] && s[i] != c)
		i++;
	i++;
	while (s[i] && s[i] != c && s[i] != '$' && !ft_isspace(s[i]))
		i++;
	return (i);
}

int	count_n_skip_env(char *s, char c, int *argc)
{
	int		i;
	char	*env;

	i = 0;
	i++;
	env = getenv_(&s[i], &i, 0);
	if (ft_isspace(s[i]) || !s[i])
		(*argc)++;
	*argc += env_has_space(env, c);
	while (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_')
		i++;
	return (i);
}

int	count_n_skip(char *s, int *argc)
{
	int	i;
	int	already;

	i = 0;
	already = 0;
	(*argc)++;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (is_q(s[i]))															// 따옴표면 어차피 스플릿은 안하니까, argc 는 그대로
			i += skip_q(&s[i]) - 1;
		if (s[i] == '$')
		{
			if (i > 0 && s[i - 1] && !ft_isspace(s[i - 1]))						// 이전 문자랑 붙어있고
			{
				if (has_leading_space(getenv_(&s[i + 1], NULL, 0)))				// 이번 확장이 공백으로 시작하면
					*argc += 1;													// 한칸 더 (안붙이고 두개의 인자가 됨)
			}
			if (s[next_idx(s, i + 1)] && !ft_isspace(s[next_idx(s, i + 1)]))	// 다음에 붙어있는 문자가 있고
			{
				if (has_trailing_space(getenv_(&s[i + 1], NULL, 0)))			// 이번 확장이 공백으로 끝나면
					*argc += 1;													// 한칸 더 (안붙이고 두개의 인자가 됨)
			}																	// ==> 근데 공백으로 끝나고, 다음번이 공백으로 시작하면
																				// ==> 다음번 검사에서 중복으로 argc+=1 될듯.
			i += count_n_skip_env(&s[i], s[i], argc) - 1;						// ==> quotes 안에 있어서 확장 대상이 아닐수도 있음.
		}
		i++;
	}
	return (i);
}

/* count how many args there are */
void	cnt_strs(char *s, int *argc)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && !ft_isspace(s[i]))
			i += count_n_skip(&s[i], argc);
		while (ft_isspace(s[i]))
			i++;
	}
}

/* memory allocations of argv */
char	**malloc_strs(char *s, int *argc)
{
	char	**ret;

	cnt_strs(s, argc);
	printf("argc = %d\n", *argc);
	ret = (char **)calloc_(*argc + 1, sizeof(char *));
	return (ret);
}

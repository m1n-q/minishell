/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:54:32 by mishin            #+#    #+#             */
/*   Updated: 2021/11/07 19:52:15 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp(char *a, char *b)
{
	int	la;
	int	lb;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	if (la >= lb)
		return (ft_strncmp(a, b, la));
	else
		return (ft_strncmp(a, b, lb));
}

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quick_sort(char	**arr, int start, int end)
{
	int		l;
	int		r;

	if (end - start + 1 <= 1)
		return ;
	if (end - start + 1 == 2)
	{
		if (cmp(arr[start], arr[end]) > 0)
			swap(&arr[start], &arr[end]);
		return ;
	}
	l = start;
	r = end - 1;
	while (l < r)
	{
		while (l < end && cmp(arr[l], arr[end]) < 0)
			l++;
		while (r > start && cmp(arr[r], arr[end]) > 0)
			r--;
		if (l < r)
			swap(&arr[l], &arr[r]);
	}
	swap(&arr[l], &arr[end]);
	quick_sort(arr, start, l - 1);
	quick_sort(arr, l + 1, end);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:54:32 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 22:06:13 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

//FIXME
void	quick_sort(char	**arr, int start, int end)
{
	int		p;
	int		l;
	int		r;

	if (end - start + 1 <= 1)
		return ;
	p = end;
	l = start;
	r = end - 1;
	while (l < r)
	{
		while (l < end && ft_strncmp(arr[l], arr[p], ft_strlen(arr[p])) < 0)
			l++;
		while (r > start && ft_strncmp(arr[r], arr[p], ft_strlen(arr[p])) > 0)
			r--;
		if (l < r)
			swap(&arr[l], &arr[r]);
	}
	swap(&arr[l], &arr[p]);
	quick_sort(arr, 0, l - 1);
	quick_sort(arr, l + 1, end);
}

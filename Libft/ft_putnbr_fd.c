/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 15:10:41 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recur(long long llnb, int fd)
{
	char	c;

	c = llnb % 10 + '0';
	if (!llnb)
		return ;
	recur(llnb / 10, fd);
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long		llnb;

	llnb = n;
	if (llnb)
	{
		if (llnb < 0)
		{
			llnb = -llnb;
			write(fd, "-", 1);
		}
		recur(llnb, fd);
	}
	else
		write(fd, "0", 1);
}

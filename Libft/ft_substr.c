/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:30:06 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:52:37 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	srclen;

	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	ret = (char *)ft_calloc((len <= srclen ? len : srclen) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < len && start + i < srclen)
		ret[i] = s[start + i];
	return (ret);
}

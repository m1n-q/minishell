/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42.kr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:28:09 by mishin            #+#    #+#             */
/*   Updated: 2021/05/11 16:28:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	t_list	*prev;
	void	*new_content;

	head = NULL;
	prev = NULL;
	new = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new = ft_lstnew(new_content);
		if (!head)
			head = new;
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		if (prev)
			prev->next = new;
		prev = new;
		lst = lst->next;
	}
	return (head);
}

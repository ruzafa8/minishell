/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:40:18 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/05/08 15:08:16 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new_node;
	void	*new_content;

	res = 0;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, new_node);
		lst = lst->next;
	}
	return (res);
}

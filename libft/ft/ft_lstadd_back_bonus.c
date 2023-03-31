/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruzafa- <aruzafa-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:25:35 by aruzafa-          #+#    #+#             */
/*   Updated: 2022/04/27 11:04:42 by aruzafa-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cpy;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cpy = *lst;
	while (cpy->next)
		cpy = cpy->next;
	cpy->next = new;
}

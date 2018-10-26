/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 16:56:41 by adayrabe          #+#    #+#             */
/*   Updated: 2018/01/28 16:56:44 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **head, t_list *elem)
{
	t_list *temp;

	if (!head)
	{
		head = (t_list **)malloc(sizeof(t_list *));
		if (elem)
		{
			*head = ft_lstnew(elem->content, elem->content_size);
			(*head)->next = elem->next;
		}
		else
			*head = NULL;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = elem;
}

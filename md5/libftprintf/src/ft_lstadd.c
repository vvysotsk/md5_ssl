/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adayrabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:26:24 by adayrabe          #+#    #+#             */
/*   Updated: 2018/01/23 16:26:29 by adayrabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst)
	{
		new->next = *alst;
		*alst = new;
	}
	else
	{
		alst = (t_list **)malloc(sizeof(t_list *));
		if (new)
		{
			*alst = ft_lstnew(new->content, new->content_size);
			(*alst)->next = new->next;
		}
		else
			*alst = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 02:52:05 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/26 03:46:48 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_msg	*lstadd(t_msg **lst)
{
	t_msg	*new;
	t_msg	*elem;

	new = malloc(sizeof(*new));
	new->next = NULL;
	if (*lst)
	{
		elem = *lst;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
	return (new);
}

void	lstclr(t_msg *lst)
{
	t_msg	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	lstprint(t_msg *lst)
{
	while (lst)
	{
		ft_printf("%s", lst->s);
		lst = lst->next;
	}
}

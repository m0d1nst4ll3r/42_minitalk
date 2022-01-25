/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:14:32 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/02 17:46:12 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pflist	*printf_lstnew(char c)
{
	t_pflist	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

void	printf_lstadd_front(t_pflist **list, char c)
{
	t_pflist	*new;

	if (! list)
		return ;
	new = printf_lstnew(c);
	if (!new)
		return ;
	new->next = *list;
	*list = new;
}

void	printf_lstadd_back(t_pflist **list, char c)
{
	t_pflist	*new;
	t_pflist	*tmp;

	if (! list)
		return ;
	new = printf_lstnew(c);
	if (!new)
		return ;
	if (! *list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	printf_lstsize(t_pflist *list)
{
	int	i;

	i = 0;
	if (! list)
		return (0);
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void	printf_lstclear(t_pflist *list)
{
	t_pflist	*elem;

	while (list)
	{
		elem = list;
		list = list->next;
		free(elem);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 03:26:05 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/26 03:26:43 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	print_chunk(char *s)
{
	int	i;

	i = -1;
	while (++i < CHUNK_SIZE && s[i])
		write(1, s + i, 1);
}

void	print_msg(int pid, t_msg *lst)
{
	ft_printf("Message from %d :\n", pid);
	while (lst)
	{
		print_chunk(lst->s);
		lst = lst->next;
	}
	ft_printf("\n");
}

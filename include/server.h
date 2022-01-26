/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 03:06:59 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/26 04:23:41 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

//size of one element's string
# define CHUNK_SIZE		1000

# include "minitalk.h"
# include <stdlib.h> //malloc and free

typedef struct s_msg
{
	char			s[CHUNK_SIZE];
	struct s_msg	*next;
}					t_msg;

//	print.c
void	print_msg(int pid, t_msg *lst);

//	list.c
t_msg	*lstadd(t_msg **lst);
void	lstclr(t_msg *lst);
void	lstprint(t_msg *lst);

#endif

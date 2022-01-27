/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 03:39:09 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/27 18:05:36 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	g_bit = -1;

//	clients send two signals representing 0 or 1 bits
static void	handle_sigusr(int sig)
{
	if (sig == BIT_0)
		g_bit = 0;
	else
		g_bit = 1;
}

//	clients send their pid first
//	if we got 15 bits, we are good
//	else, something went wrong, go back to main loop
static int	get_pid(void)
{
	int	pid;
	int	i;

	pid = 0;
	i = 0;
	while (g_bit != -1 && i < 32)
	{
		pid = pid | g_bit << i;
		i++;
		g_bit = -1;
		if (i < 32)
			usleep(PID_TIMEOUT_S);
	}
	if (i < 32)
	{
		ft_printf("Received incomplete PID...\n");
		return (-1);
	}
	return (pid);
}

static int	get_msg2(t_msg **lst, t_msg **elem, int i[3])
{
	i[2] = -1;
	if (i[0])
		(*elem)->s[i[1]] = (*elem)->s[i[1]] | g_bit << i[0];
	else
		(*elem)->s[i[1]] = g_bit;
	g_bit = -1;
	i[0]++;
	if (i[0] == 8)
	{
		if (!(*elem)->s[i[1]])
			return (1);
		i[0] = 0;
		i[1]++;
		if (i[1] == CHUNK_SIZE)
		{
			*elem = lstadd(lst);
			i[1] = 0;
		}
	}
	return (0);
}

//	i :
//	0	bit index
//	1	byte index
//	2	retry amount
static void	get_msg(int pid)
{
	t_msg	*lst;
	t_msg	*elem;
	int		i[3];

	lst = NULL;
	elem = lstadd(&lst);
	i[0] = 0;
	i[1] = 0;
	i[2] = -1;
	while (++i[2] < MAX_RETRIES)
	{
		if (g_bit != -1)
			if (get_msg2(&lst, &elem, i))
				break ;
		kill(pid, SIGUSR1);
		usleep(MSG_TIMEOUT_S);
	}
	if (i[2] == MAX_RETRIES)
		ft_printf(" -- Lost connection to client... Aborting\n");
	else
	{
		kill(pid, SIGUSR1);
		print_msg(pid, lst);
	}
	lstclr(lst);
}

//	./server
//	1. display own pid
//	2. wait for a signal
//	  2a. on signal, try to read pid
//	  2b. if pid was correct, try to read msg
//	  2c. reset loop after success or timeout
int	main(void)
{
	struct sigaction	sa;
	int					pid;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID : %d\n", getpid());
	while (1)
	{
		if (g_bit != -1)
		{
			pid = get_pid();
			if (pid != -1)
				get_msg(pid);
		}
		pause();
	}
	return (0);
}

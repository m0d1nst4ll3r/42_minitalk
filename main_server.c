/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 03:39:09 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/25 01:00:10 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit;

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
	while (g_bit != -1 && i < 15)
	{
		pid = pid | g_bit << i;
		i++;
		g_bit = -1;
		if (i < 15)
			usleep(PID_TIMEOUT_S);
	}
	if (i < 15)
	{
		ft_printf("Received incomplete PID...\n");
		return (-1);
	}
	return (pid);
}

//	fill next bit of byte
//	if byte is complete and 0, return 1 (end of file)
//	if byte is complete and non-0, write it
static int	get_msg_bitwise(char *b, int *i)
{
	if (++*i == 8)
	{
		if (!*b)
		{
			g_bit = -1;
			write(1, "\n", 1);
			return (1);
		}
		*i = 0;
		write(1, b, 1);
		*b = 0;
	}
	*b = *b | g_bit << *i;
	g_bit = -1;
	return (0);
}

//	1. send ready signal to client
//	2. wait for response
//		2a. retry if no response
//		2b. exit after max retries
//	3. add bit and write if 8 bits
//	4. go back to 1.
static void	get_msg(int pid)
{
	char	b;
	int		j;
	int		i;

	b = 0;
	i = -1;
	j = -1;
	while (++j < MAX_RETRIES)
	{
		if (g_bit != -1)
		{
			j = -1;
			if (get_msg_bitwise(&b, &i))
			{
				kill(pid, SIGUSR1);
				break ;
			}
		}
		kill(pid, SIGUSR1);
		usleep(MSG_TIMEOUT_S);
	}
	if (j == MAX_RETRIES)
		ft_printf(" -- Lost connection to client... Aborting\n");
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
	g_bit = -1;
	while (1)
	{
		if (g_bit != -1)
		{
			pid = get_pid();
			if (pid != -1)
			{
				ft_printf("Message from %d :\n", pid);
				get_msg(pid);
			}
		}
		pause();
	}
	return (0);
}

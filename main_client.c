/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 03:40:40 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/27 17:48:26 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	g_response_received;

//	The server sends a signal when it has resolved the client's PID
//	And to confirm each bit of received data
static void	handle_sigusr(int sig)
{
	(void)sig;
	g_response_received = 1;
}

//	Once the message is over, send 8 zeroes to end transmission
static int	send_eof(int pid)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (i < 8 && ++j < MAX_RETRIES)
	{
		if (g_response_received)
		{
			j = -1;
			i++;
			g_response_received = 0;
		}
		kill(pid, BIT_0);
		usleep(MSG_TIMEOUT_C);
	}
	if (j == MAX_RETRIES)
		return (1);
	return (0);
}

//	g_response_received is always 1 when entering
//	send bit by bit, 8 bits per char, until \0
static int	send_message(int pid, char *msg)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (*msg && ++j < MAX_RETRIES)
	{
		if (g_response_received)
		{
			j = -1;
			if (++i == 8)
			{
				i = 0;
				msg++;
			}
			g_response_received = 0;
		}
		if (1 & *msg >> i)
			kill(pid, BIT_1);
		else
			kill(pid, BIT_0);
		usleep(MSG_TIMEOUT_C);
	}
	return (*msg);
}

//	PID is 15 bits
//	send 15 bits, then wait for answer
//	if no answer came before timeout, try again
//	only try a certain amount of times before aborting
static int	send_pid(int pid_s, int pid_c)
{
	int	i;
	int	j;

	j = -1;
	g_response_received = 0;
	while (!g_response_received && ++j < MAX_RETRIES)
	{
		i = -1;
		while (++i < 32)
		{
			if (1 & pid_c >> i)
				kill(pid_s, BIT_1);
			else
				kill(pid_s, BIT_0);
			if (i < 31)
				usleep(PID_SLEEP);
		}
		usleep(PID_TIMEOUT_C);
	}
	if (!g_response_received)
		return (1);
	return (0);
}

//	./client [pid] [message]
//	1. send pid to server, wait for response
//	2. send message to server (back and forth signals)
//	3. send last 8 bits
//	exit properly once the last response is received
//	timeouts and max retries are set to avoid infinite loops
int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					pid_c;
	int					pid_s;

	if (ac != 3)
		return (ft_printf("Invalid argument count :(\n") || 1);
	if (!ft_isint(av[1]))
		return (ft_printf("Invalid PID :(\n") || 1);
	pid_s = ft_atoi(av[1]);
	if (!pid_s)
		return (ft_printf("Invalid PID :(\n") || 1);
	sa.sa_handler = &handle_sigusr;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	pid_c = getpid();
	if (send_pid(pid_s, pid_c))
		return (ft_printf("Could not send PID to server... Aborting :(\n") || 1);
	if (send_message(pid_s, av[2]))
		return (ft_printf("Server stopped responding... Aborting :(\n") || 1);
	if (send_eof(pid_s))
		return (ft_printf("Server stopped responding... Aborting :(\n") || 1);
	ft_printf("Message sent successfully ^-^\n");
	return (0);
}

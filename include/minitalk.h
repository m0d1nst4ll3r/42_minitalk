/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 03:39:28 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/25 01:37:02 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define BIT_0			SIGUSR1
# define BIT_1			SIGUSR2
//max amount of retries before giving up
# define MAX_RETRIES	20
//time client waits in-between each PID bit
# define PID_SLEEP		1000
//time to wait for client to finish sending PID before server resets state
# define PID_TIMEOUT_S	3000
//time to wait for server confirmation before client resends PID
# define PID_TIMEOUT_C	5000
//time to wait for client msg before resending confirmation
# define MSG_TIMEOUT_S	3000
//time to wait for server confirmation before client resends msg
# define MSG_TIMEOUT_C	2000

# include <sys/types.h> //getpid and kill
# include <unistd.h> //getpid and sleep
# include <signal.h> //to use signals
# include <stdlib.h> //malloc free
# include "ft_printf.h"

int	ft_atoi(const char *str);
int	ft_isint(const char *s);

#endif

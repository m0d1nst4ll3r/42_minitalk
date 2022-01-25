/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:10:35 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/24 04:26:21 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//	Searches for c in s
//	Returns the address of the first occurence of c
//		or NULL if not found
char	*ft_strchr(char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}

//	Converts an int into a decimal / hexadecimal value
//	The int has to be between 0 and 15
char	ft_get_char(int i, char type)
{
	if (i < 10)
		return (i + '0');
	else if (type == 'X')
		return (i - 10 + 'A');
	else
		return (i - 10 + 'a');
}

//	Modified atoi which refuses any initial 0
//	Modifies the index directly
int	ft_atoi_printf(char *s, int *i)
{
	int	res;

	res = 0;
	if (s[*i] == 0)
		return (0);
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		res = res * 10 + s[*i] - '0';
		(*i)++;
	}
	(*i)--;
	return (res);
}

long int	ft_abs(long int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:29:03 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/05 15:17:11 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* -------------------------------------------------------------------- **
**		printf_pad
**
**	Adds a certain amount of a certain character either at the start
**		of the provided list, or at the end.
**
**	The list we receive is not the start of the entire list of bytes
**		that contains the string we are printing. Rather, it represents
**		where we currently are in the string, and more specifically,
**		where we want the padding to be written.
**
**	- list		the element in our list where we'll start writing
**				our padding characters
**	- len		the amount of characters to write
**	- dir		where to write the characters (l for left, r for right)
**	- fill		what character to add (typically either 0 or ' ')
** -------------------------------------------------------------------- */
void	printf_pad(t_pflist **list, int len, char dir, char fill)
{
	while (len > 0)
	{
		if (dir == 'l')
			printf_lstadd_front(list, fill);
		else
			printf_lstadd_back(list, fill);
		len--;
	}
}

/* -------------------------------------------------------------------- **
**		printf_i_rec
**
**	Prints a number in a certain base.
**
**	Used first in printf_i or printf_u conversions.
**	Flags are handled after this first print.
**
**	- i			the (signed or unsigned) int to print
**	- base		the base in which to convert
**	- type		x or X, defines lowercase or uppercase hexadecimal
**	- list		the element to start writing from in the list
** -------------------------------------------------------------------- */
static void	printf_i_rec(long int i, int base, char type, t_pflist **list)
{
	if (i >= base)
		printf_i_rec(i / base, base, type, list);
	printf_lstadd_back(list, ft_get_char(i % base, type));
}

/* -------------------------------------------------------------------- **
**		printf_i
**
**	Order :
**		1. the number alone (no '-')
**		2. dot padding
**		3. sign, or ' '
**		4. zero padding
**		5. blank padding
**
**	The following flags are taken into account :
**		- space		adds a ' ' before value if positive
**		- plus		adds a '+' before value if positive
**		- dot		pad with '0' to the left (ignores non-digits)
**		- zero		pad with '0' to the left (includes non-digits)
**		- width		pad with ' ' to the left
**		- minus		pad with ' ' to the right
**
**	- i			the signed int to print
**	- list		the element to start writing from in the list
**	- flags		the flags (such as #05-8) in structure form
** -------------------------------------------------------------------- */
void	printf_i(long int i, t_pflist **list, t_pfflags flags)
{
	if (flags.dot || i)
		printf_i_rec(ft_abs(i), 10, 0, list);
	if (flags.dot > 0)
		printf_pad(list, flags.dot - printf_lstsize(*list), 'l', '0');
	if (i < 0)
		printf_lstadd_front(list, '-');
	else if (flags.space >= 0)
		printf_lstadd_front(list, ' ');
	else if (flags.plus >= 0)
		printf_lstadd_front(list, '+');
	if (flags.zero >= 0)
	{
		if (i < 0 || flags.space >= 0 || flags.plus >= 0)
			printf_pad(&((*list)->next), flags.zero - printf_lstsize(*list),
				'l', '0');
		else
			printf_pad(list, flags.zero - printf_lstsize(*list), 'l', '0');
	}
	if (flags.width > 0)
		printf_pad(list, flags.width - printf_lstsize(*list), 'l', ' ');
	if (flags.minus > 0)
		printf_pad(list, flags.minus - printf_lstsize(*list), 'r', ' ');
}

/* -------------------------------------------------------------------- **
**		printf_u
**
**	Order :
**		1. the number
**		2. dot padding
**		3. hex prefix '0x'
**		4. zero padding
**		5. blank padding
**
**	The following flags are taken into account :
**		- sharp		adds a '0x' before the hexadecimal value
**		- dot		pad with '0' to the left (ignores non-digits)
**		- zero		pad with '0' to the left (includes non-digits)
**		- width		pad with ' ' to the left
**		- minus		pad with ' ' to the right
**
**	- u			the unsigned int to print
**	- type		the type (u, x, X) of the conversion
**	- list		the element to start writing from in the list
**	- flags		the flags (such as #05-8) in structure form
** -------------------------------------------------------------------- */
void	printf_u(unsigned int u, char type, t_pflist **list, t_pfflags flags)
{
	if (flags.dot || u)
	{
		if (type == 'x' || type == 'X')
			printf_i_rec(u, 16, type, list);
		else
			printf_i_rec(u, 10, type, list);
	}
	if (flags.dot > 0)
		printf_pad(list, flags.dot - printf_lstsize(*list), 'l', '0');
	if (u && (type == 'x' || type == 'X') && flags.sharp >= 0)
	{
		printf_lstadd_front(list, type);
		printf_lstadd_front(list, '0');
		if (flags.zero >= 0)
			printf_pad(&((*list)->next->next),
				flags.zero - printf_lstsize(*list), 'l', '0');
	}
	else if (flags.zero >= 0)
		printf_pad(list, flags.zero - printf_lstsize(*list), 'l', '0');
	if (flags.width > 0)
		printf_pad(list, flags.width - printf_lstsize(*list), 'l', ' ');
	if (flags.minus > 0)
		printf_pad(list, flags.minus - printf_lstsize(*list), 'r', ' ');
}

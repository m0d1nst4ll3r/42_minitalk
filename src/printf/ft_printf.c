/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:50:34 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/03 16:54:51 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* -------------------------------------------------------------------- **
**		ft_printf
**
**	Does what printf does, sometimes a bit better, sometimes a bit worse.
**
**	The string to format is printed into a list first, before being
**		printed onto stdout.
**		(fill_output)
**
**	Stocking the output instead of printing it right away makes it
**		easier to count the amount of characters printed.
**
**	Stocking the output into a list saves us the need to realloc
**		excessively, and allows us to insert characters and thus,
**		write characters in any order we wish, useful for flags.
**
**	The output is then printed (print_output), freed (lstclear)
**		and its length is returned. (lstsize)
**
**	- format	string to format
**	- ...		arguments to use during formatting
** -------------------------------------------------------------------- */
int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_pflist	*output;
	int			len;

	if (! format)
		return (0);
	va_start(ap, format);
	output = NULL;
	printf_fill_output((char *)format, ap, &output);
	va_end(ap);
	printf_print_output(output);
	len = printf_lstsize(output);
	printf_lstclear(output);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:52:24 by rpohlen           #+#    #+#             */
/*   Updated: 2021/12/04 14:30:07 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* -------------------------------------------------------------------- **
**		convert
**
**	Performs a conversion of type (code) with the next argument in (ap)
**		taking into account (flags) and  writing the result into (output)
**
**	The conversion is performed by a sub-function appropriate to the
**		conversion type.
**		(printf_i, etc...)
**
**	This is used when encountering a % expression, and after evaluating
**		all the flags. The code is not guaranteed to be correct.
**
**	Returns 1 when the code is correct and the conversion successful
**			0 when the code is invalid
**
**	- code		whichever character comes after the flags in the % expr
**				valid codes: u, i, d, x, X, c, s, p
**	- ap		list of arguments
**	- output	output to fill when converting
**	- flags		flag structure to use while converting
** -------------------------------------------------------------------- */
static int	convert(char code, va_list ap, t_pflist **output, t_pfflags flags)
{
	if (code == 'i' || code == 'd')
		printf_i(va_arg(ap, int), output, flags);
	else if (code == 'u' || code == 'x' || code == 'X')
		printf_u(va_arg(ap, unsigned int), code, output, flags);
	else if (code == 'c')
		printf_c((char)va_arg(ap, int), output, flags);
	else if (code == 's')
		printf_s(va_arg(ap, char *), output, flags);
	else if (code == 'p')
		printf_p(va_arg(ap, void *), output, flags);
	else
		return (0);
	return (1);
}

/* -------------------------------------------------------------------- **
**		printf_fill_output
**
**	Core function of the program.
**
**	Parses the format string, adds each character to the provided list.
**		(lstadd_back)
**
**	For % characters, the expression that follows is evaluated.
**		(flag_interpreter)
**
**	Invalid expressions are treated like regular characters.
**	Valid expressions are used to convert the next value in (ap).
**		(convert)
**
**	- code		whichever character comes after the flags in the % expr
**				valid codes: u, i, d, x, X, c, s, p
**	- ap		list of arguments
**	- output	output to fill when converting
**	- flags		flag structure to use while converting
** -------------------------------------------------------------------- */
void	printf_fill_output(char *format, va_list ap, t_pflist **output)
{
	int			i;
	int			fi;
	t_pfflags	flags;

	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			printf_reset_flags(&flags);
			fi = printf_flag_interpreter(format + i + 1, &flags);
			i += fi + 1;
			if (! fi && format[i] == '%')
				printf_lstadd_back(output, '%');
			else if (! convert(format[i], ap, printf_lstlastp(output), flags))
			{
				i -= fi + 1;
				printf_lstadd_back(output, '%');
			}
		}
		else
			printf_lstadd_back(output, format[i]);
		i++;
	}
}

//	Simply prints the list in order
void	printf_print_output(t_pflist *output)
{
	while (output)
	{
		write(1, &(output->c), 1);
		output = output->next;
	}
}

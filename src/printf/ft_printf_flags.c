/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:00:18 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/24 04:26:23 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//	Resets all of the flags to their default -1 value
//	Used right after encountering any % expression
void	printf_reset_flags(t_pfflags *flags)
{
	flags->sharp = -1;
	flags->space = -1;
	flags->plus = -1;
	flags->zero = -1;
	flags->minus = -1;
	flags->width = -1;
	flags->dot = -1;
}

/* -------------------------------------------------------------------- **
**		update_flag
**
**	When encountering a flag, updates its corresponding value
**		in the flags structure.
**
**	Flags which can have an optional value after them require
**		an atoi function to be used.
**
**	Flags which don't are simply updated to 0 to signify their
**		existence.
**
**	- s			string starting at the expression
**	- flags		flags to update accordingly
**	- i			index of the flag we are updating, in the string
** -------------------------------------------------------------------- */
static void	update_flag(char *s, t_pfflags *flags, int *i)
{
	if (s[*i] == '#')
		flags->sharp = 0;
	else if (s[*i] == ' ')
		flags->space = 0;
	else if (s[*i] == '+')
		flags->plus = 0;
	else if (s[*i] == '0')
	{
		(*i)++;
		flags->zero = ft_atoi_printf(s, i);
	}
	else if (s[*i] == '-')
	{
		(*i)++;
		flags->minus = ft_atoi_printf(s, i);
	}
	else if (s[*i] == '.')
	{
		(*i)++;
		flags->dot = ft_atoi_printf(s, i);
	}
	else if (s[*i] >= '1' && s[*i] <= '9')
		flags->width = ft_atoi_printf(s, i);
}

/* -------------------------------------------------------------------- **
**		printf_flag_interpreter
**
**	Interprets expressions following a %
**
**	Evaluates flags one by one. Upon encountering a non-flag-compliant
**		character, that character must be a code for a conversion
**		(u i d x X c s p), so we stop.
**
**	The conversion code will be evaluated outside this function.
**
**	- s			string starting at the expression to interpret
**	- flags		flags to update accordingly
** -------------------------------------------------------------------- */
int	printf_flag_interpreter(char *s, t_pfflags *flags)
{
	int	i;

	i = 0;
	while (ft_strchr("# +0-.123456789", s[i]))
	{
		update_flag(s, flags, &i);
		i++;
	}
	if (flags->space >= 0 && flags->plus >= 0)
		flags->space = -1;
	if (flags->width >= 0 && flags->minus >= 0)
		flags->width = -1;
	if ((flags->width >= 0 || flags->minus >= 0) && flags->zero >= 0)
		flags->zero = -1;
	if (flags->zero >= 0 && flags->dot >= 0)
	{
		if (flags->width < flags->zero)
			flags->width = flags->zero;
		flags->zero = -1;
	}
	return (i);
}

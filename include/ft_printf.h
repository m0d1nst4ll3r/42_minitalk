/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:08:46 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/24 04:26:42 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* -------------------------------------------------------------------- **
**	Useful features to add later:
**
**	- %m		prints the current errno with strerror(errno)
**	- %ld		for long ints
**	- %f		for doubles
**	- an fprintf which does the same thing as printf but with a channel
**		argument such as stderr or the fd of an open file.
** -------------------------------------------------------------------- */

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

//	This list will be used throughout our program to store printf's output
typedef struct s_pflist
{
	char			c;
	struct s_pflist	*next;
}					t_pflist;

/* -------------------------------------------------------------------- **
**	This structure is used to communicate flag values to sub-functions
**
**	- sharp		(#) puts a '0x' before value ('0X' for X)
**				x and X
**	- space		( ) adds a space before value if positive
**				i and d
**	- plus		(+) adds a plus before value if positive
**				i and d
**	- zero		(0n) pads value with n zeroes ('-' included)
**				u, i, d, x and X
**	- minus		(-n) pads value with n spaces to the right of the value
**				u, i, d, x, X, p, c and s
**	- width		(n) pads value with n spaces to the left of the value
**				u, i, d, x, X, p, c and s
**	- dot		(.n) effect differs depending on type of argument
**				s					limits s to n characters
**				u, i, d, x and X	pads value with n zeroes ('-' ignored)
**				can be used as (.*) to signify that the next argument
**				should be used as the flag's value.
**				can be used as (.m$), to signify that the m-th argument
**				should be used as the flag's value.
**				(.n) ignores all non-digit characters in its calculations
**
**	Padding with n characters means if value takes less than n characters,
**		add n - (length) characters to it.
**
**	When optional values are omitted, they are considered to be 0.
**	Sometimes, this means the flag is useless (ex: %.i), other times,
**		the flag can still have an effect (ex: %.s).
**	This is reflected by the flag having a negative value (typically, -1)
**		when it is absent and 0 when it is present with a 0 value.
**
**	Ambiguous cases:
**	- '0x' with any padding : the '0x' is counted in the length
**	- ' ' or '+' with any padding : the ' ' or '+' is counted
**	- ' ' and '+' both present : '+' takes precedence
**	- width and minus both present : width is ignored (see error case)
**	- dot with '0x' : the '0x' is ignored
**	- dot with ' ' or '+' : both are ignored
**	- dot with width or minus : the zeroes are added before the spaces
**	- dot with 0 : 0 is completely ignored and taken out of the flag
**		if a value followed the 0, it is counted as a width value
**
**	Error cases:
**	- incompatible flag/conversion (ex: %#i)
**		we ignore the flags and so does the official printf
**	- incompatible flags (ex: width and minus)
**		we always consider that flags have a priority
**		the official printf only ignores incompatible flags when they
**		have no values associated with them, otherwise it will count
**		their values as an incompatible string of regular characters
**		and print the entire expression
**	- flag redefinition, last flag definition is used
**		this behavior differs from the official printf which considers
**		flag redefinition to be valid only as long as the optional
**		values are redefined only once and for the last flag occurence
** -------------------------------------------------------------------- */
typedef struct s_pfflags
{
	int	sharp;
	int	space;
	int	plus;
	int	zero;
	int	minus;
	int	width;
	int	dot;
}		t_pfflags;

//	ft_printf_utils.c
char		*ft_strchr(char *s, char c);
char		ft_get_char(int i, char type);
int			ft_atoi_printf(char *s, int *i);
long int	ft_abs(long int i);

//	ft_printf_utils_list.c
void		printf_lstadd_front(t_pflist **list, char c);
void		printf_lstadd_back(t_pflist **list, char c);
int			printf_lstsize(t_pflist *list);
void		printf_lstclear(t_pflist *list);
t_pflist	**printf_lstlastp(t_pflist **list);

//	ft_printf_args.c
void		printf_pad(t_pflist **list, int len, char dir, char fill);
void		printf_i(long int i, t_pflist **list, t_pfflags flags);
void		printf_u(unsigned int u, char type, t_pflist **list,
				t_pfflags flags);

//	ft_printf_args2.c
void		printf_c(char c, t_pflist **list, t_pfflags flags);
void		printf_s(char *s, t_pflist **list, t_pfflags flags);
void		printf_p(void *p, t_pflist **list, t_pfflags flags);

//	ft_printf_flags.c
int			printf_flag_interpreter(char *s, t_pfflags *flags);
void		printf_reset_flags(t_pfflags *flags);

//	ft_printf_output.c
void		printf_fill_output(char *format, va_list ap, t_pflist **output);
void		printf_print_output(t_pflist *output);

//	ft_printf.c
int			ft_printf(const char *format, ...);

#endif

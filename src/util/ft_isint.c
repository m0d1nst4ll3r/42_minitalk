/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:49:09 by rpohlen           #+#    #+#             */
/*   Updated: 2022/01/24 07:17:05 by rpohlen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isint(const char *s)
{
	if (!s || !*s)
		return (0);
	while (*s)
	{
		if ((*s ^ '0') > 9)
			return (0);
		s++;
	}
	return (1);
}

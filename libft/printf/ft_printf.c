/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:23:33 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/29 13:19:49 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
#include <stdarg.h>

size_t	check_conversions(va_list args, char const *str)
{	
	++str;
	if (*str == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (*str == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (*str == 'p')
		return (ft_printadd(va_arg(args, void *)));
	else if (*str == 'd')
		return (ft_printnbr(va_arg(args, int)));
	else if (*str == 'i')
		return (ft_printnbr(va_arg(args, int)));
	else if (*str == 'u')
		return (ft_printunbr(va_arg(args, unsigned int)));
	else if (*str == 'x')
		return (ft_printhex(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (*str == 'X')
		return (ft_printhex(va_arg(args, unsigned int), "0123456789ABCDEF"));
	else if (*str == '%')
		return (ft_printchar('%'));
	else
		return (-1);
}

int	ft_printf(char const *str, ...)
{	
	size_t	n;
	va_list	args;
	size_t	total;

	n = 0;
	total = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str)
	{	
		if (*str == '%')
		{
			n = check_conversions(args, str);
			str++;
		}
		else
			n = ft_printchar(*str);
		if ((int) n == -1)
			return (-1);
		total += n;
		str++;
	}
	va_end(args);
	return (total);
}

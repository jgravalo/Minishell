/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:55:57 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/27 17:22:57 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr(int n)
{
	long	number;
	size_t	count;

	count = 0;
	number = 0;
	number = (long) n;
	if (number < 0)
	{
		number *= -1;
		ft_putchar('-');
	}
	if (number > 9)
	{
		ft_putnbr(number / 10);
		ft_putnbr(number % 10);
	}
	if (number <= 9)
	{
		ft_putchar(number + '0');
		count++;
	}
	return (count);
}

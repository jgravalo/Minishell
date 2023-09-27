/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:55:57 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/29 13:20:02 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static size_t	ft_num_len(long number)
{	
	size_t	len;

	len = 1;
	if (number < 0)
	{
		len++;
		number *= -1;
	}
	while (number / 10)
	{
		number /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_create_string(long int number, char *str, size_t len)
{
	while (number > 0)
	{
		str[len - 1] = number % 10 + '0';
		number /= 10;
		len--;
	}
	return (str);
}

size_t	ft_printnbr(int n)
{
	long	number;
	size_t	count;
	size_t	len;
	char	*str;

	number = (long) n;
	len = ft_num_len(number);
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (!str)
		return (-1);
	str[len] = '\0';
	if (number < 0)
	{
		str[0] = '-';
		number *= -1;
	}
	if (number == 0)
		str[len - 1] = '0';
	str = ft_create_string(number, str, len);
	count = ft_putstr(str);
	free (str);
	str = NULL;
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:55:57 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/10 09:01:19 by theonewhokn      ###   ########.fr       */
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

size_t	ft_printnbr(int fd, int n)
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
	count = ft_printstr(fd, str);
	free (str);
	str = NULL;
	return (count);
}

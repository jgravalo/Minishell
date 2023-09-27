/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:28:29 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/29 13:19:37 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>
#include <unistd.h>

static size_t	ft_add_len(unsigned long temp, size_t len)
{
	while (temp > 15)
	{
		temp /= 16;
		len++;
	}
	return (len + 1);
}

static char	*ft_create_arr(char *str,
		unsigned long temp, unsigned long n, int i)
{
	str[i + 1] = '\0';
	while (i >= 0)
	{
		temp = n % 16;
		if (temp > 9)
			str[i] = temp + 87;
		else
			str[i] = temp + '0';
		n /= 16;
		i--;
	}
	return (str);
}

static char	*ft_free(char *str)
{
	free (str);
	str = NULL;
	return (NULL);
}

size_t	ft_printadd(void *ptr)
{
	size_t			len;
	unsigned long	n;
	unsigned long	temp;
	char			*str;

	len = 0;
	str = NULL;
	if (!ptr)
		return (ft_putstr("0x0"));
	n = (unsigned long int) ptr;
	temp = n;
	len = ft_add_len(temp, len);
	str = (char *)malloc(sizeof (char) * (len + 1));
	if (!str)
		return (-1);
	str = ft_create_arr(str, temp, n, len - 1);
	n = ft_putstr("0x");
	if ((int) n == -1)
	{	
		str = ft_free(str);
		return (-1);
	}
	n += ft_putstr(str);
	str = ft_free(str);
	return (n);
}

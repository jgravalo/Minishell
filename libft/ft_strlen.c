/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:04:33 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:50:18 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	unsigned int	c;

	c = 0;
	while (*s)
	{
		c++;
		s++;
	}
	return (c);
}
/*
int main(void)
{
    char *str = "Hello boys and girls!";

    printf("%ld", ft_strlen(str));
}
*/

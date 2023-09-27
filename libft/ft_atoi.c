/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:30 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/09/27 19:35:37 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int64_t	ft_atoi(char *str)
{
	int64_t	n;
	int		sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t'
		|| *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		n = n * 10 + (*str - 48);
		str++;
	}
	return (n * sign);
}
/*
#include <stdio.h>

int main(void)
{
    int n;
    char str[] = "+12345";
    n = ft_atoi(str);
    printf("%d", n);
}
*/
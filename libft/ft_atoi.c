/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:05:30 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:33:11 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	result = 0;
	i = 0;
	sign = 0;
	while (is_space(str[i]) == 1)
		i++;
	while ((str[i] == 43 || str[i] == 45) && sign == 0)
	{
		if (str[i] == 45)
			sign = 2;
		else
			sign = 1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (sign == 2)
		result *= -1;
	return (result);
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
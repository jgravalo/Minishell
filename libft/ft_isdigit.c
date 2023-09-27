/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:06:10 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:32:24 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char c = '2';

    printf("%d", ft_isdigit(c));
}
*/

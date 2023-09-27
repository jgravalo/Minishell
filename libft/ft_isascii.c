/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:00:50 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:32:32 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char c = 220;

    printf("%d", ft_isascii(c));
}
*/

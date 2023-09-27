/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:01:17 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:32:28 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char c =  '\n';

    printf("%d", ft_isprint(c));
}
*/

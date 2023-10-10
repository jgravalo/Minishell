/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:54:31 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/10 08:58:30 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_printchar(int fd, char c)
{
	size_t	n;

	n = 0;
	if (write(fd, &c, 1) == -1)
		return (-1);
	n++;
	return (n);
}

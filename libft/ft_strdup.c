/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:29:42 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/04 13:47:27 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;

	dup = (char *)malloc(sizeof (char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, ft_strlen(s1) + 1);
	return (dup);
}
/*
#include <stdio.h>

int main(void)
{
    char *str;
	char *dup;

    str = "Hola";
    dup = ft_strdup(str);
	printf("%s", dup);
   
}
*/

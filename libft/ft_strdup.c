/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:29:42 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/09/27 17:04:33 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
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

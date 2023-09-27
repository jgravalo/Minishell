/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:19 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/09/27 13:56:57 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"

char *add_without_plus(char *var)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	new = malloc(sizeof (char) * ft_strlen(var));
	while(var[i])
	{	
		if (var[i] != '+')
			new[j++] = var[i++];
		else
			i++;
	}
	new[j] = '\0';
	return (new);
}
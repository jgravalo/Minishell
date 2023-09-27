/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:16:39 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/27 16:51:34 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_m(char **fdf)
{
	int	i;

	i = 0;
	if (fdf)
	{
		while (fdf[i])
		{
			free(fdf[i]);
			i++;
		}
		free(fdf);
	}
}

int	count_arr(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

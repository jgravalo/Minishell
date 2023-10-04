/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:49:12 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:04:13 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

void	create_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh->pipes)
	{
		sh->p = (t_pipe *)malloc(sizeof(t_pipe) * (sh->pipes));
		check_malloc_error(sh->p);
		while (i < sh->pipes)
		{
			pipe(sh->p[i].p);
			i++;
		}
	}
}

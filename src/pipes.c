/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:49:12 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/27 11:53:31 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh->pipes)
	{
		sh->p = (t_pipe *)malloc(sizeof(t_pipe) * (sh->pipes));
		while (i < sh->pipes)
		{
			pipe(sh->p[i].p);
			i++;
		}
	}
}

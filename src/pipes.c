/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 08:49:12 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 09:15:22 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	create_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	sh->p = (t_pipe *)malloc(sizeof(t_pipe) * (sh->pipes));
	while (i < sh->pipes)
	{
		pipe(sh->p[i].p);
		i++;
	}
}

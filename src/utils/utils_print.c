/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:48:54 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/26 19:28:51 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	ft_printarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	ft_print_intarr(int *arr, int n)
{
	int	i;

	i = 0;
	while (n)
	{
		printf("%d", arr[i]);
		i++;
		n--;
	}
	printf("\n");
}

void	ft_printcmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("args son:\n");
		ft_printarglist(cmd[i]->arg);
		ft_printredirlist(cmd[i]->red);
		i++;
	}
}

void	ft_printcmdargx(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("argxs son:\n");
		ft_printarglist(cmd[i]->arg_x);
		if (cmd[i]->red_x)
			ft_printredirlist(cmd[i]->red_x);
		i++;
	}
}

void	ft_printredirlist(t_redir *red)
{
	while (red)
	{
		printf("redir type %d\n", red->type);
		ft_printredirarglist(red->arg);
		red = red->next;
	}
}

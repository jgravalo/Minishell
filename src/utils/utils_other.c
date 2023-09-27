/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:16:39 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/27 16:45:03 by dtome-pe         ###   ########.fr       */
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

int64_t	ft_atoi(char *str)
{
	int64_t	n;
	int		sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t'
		|| *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		n = n * 10 + (*str - 48);
		str++;
	}
	return (n * sign);
}

uint64_t	ft_u_atoi(char *str)
{
	uint64_t	n;
	int			sign;

	n = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t'
		|| *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		n = n * 10 + (*str - 48);
		str++;
	}
	return (n * sign);
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

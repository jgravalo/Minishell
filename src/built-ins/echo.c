/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:58:59 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 09:53:40 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/utils.h"
#include "../libft/libft.h"

static int	is_n_option(char *argv)
{
	int	i;

	i = 2;
	if (!argv)
		return (1);
	if (ft_strncmp(argv, "-n", 2) == 0)
	{
		while (argv[i])
		{
			if (argv[i] == 'n')
				i++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

int	echo(char **argv)
{
	int		i;

	i = 1;
	if (argv[1] == NULL)
	{
		ft_printf(1, "\n");
		return (0);
	}
	while (is_n_option(argv[i]) == 0)
		i++;
	while (argv && argv[i])
	{
		ft_printf(1, "%s", argv[i]);
		if (argv[i + 1])
			ft_printf(1, " ", 1);
		i++;
	}
	if (!argv[1] || (argv[1] && is_n_option(argv[1]) != 0))
		ft_printf(1, "\n", 1);
	return (0);
}

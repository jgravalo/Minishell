/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:58:59 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 14:05:42 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	char	*new;

	i = 1;
	if (argv[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (is_n_option(argv[i]) == 0)
		i++;
	while (argv && argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!argv[1] || (argv[1] && is_n_option(argv[1]) != 0))
		write(1, "\n", 1);
	return (0);
}

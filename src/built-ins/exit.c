/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:37:09 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/10 09:56:07 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../libft/libft.h"

static int	is_it_numeric(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[i] == ' ')
		i++;
	if (is_digit(line[i]) || ((line[i] == '-' || line[i] == '+')
			&& is_digit(line[i + 1]) == 1))
		i++;
	else
		return (1);
	while (is_digit(line[i]))
		i++;
	if (line[i] == ' ' || line[i] == '\0')
	{
		while (line[i])
		{
			if (line[i] != ' ')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

static void	exit_message(t_shell *sh, int type, char *argument)
{
	if (type == 2)
	{
		ft_printf(2, "bash: exit: %s: numeric argument required\n", argument);
		exit(255);
	}
	else
	{
		ft_printf(2, "bash: exit: too many arguments\n");
		sh->exit = 1;
	}
}

void	ft_exit(t_shell *sh, t_cmd **cmd, int i)
{
	if (cmd[i]->args[1] != NULL)
	{
		if (ft_strcmp(cmd[i]->args[1], "--") == 0)
			exit(sh->exit);
		if (compare_exit(cmd[i]->args[1]) || is_it_numeric(cmd[i]->args[1]))
			exit_message(sh, 2, cmd[i]->args[1]);
		if (cmd[i]->args[2] != NULL)
			exit_message(sh, 1, cmd[i]->args[1]);
		else
			exit(ft_atoi(cmd[i]->args[1]));
	}
	else
		exit(sh->exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:37:09 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/14 15:47:05 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_it_numeric(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (1);
	while (line[i] == ' ')
		i++;
	if (is_digit(line[i]) || ((line[i] == '-' || line[i] == '+') && is_digit(line[i + 1]) == 1))
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

static int	check_long_min(int64_t number)
{
	uint64_t	u_number;
	uint64_t	min;

	min = (uint64_t) LONG_MIN * -1;
	u_number = number * -1;
	if (u_number > LONG_MIN)
		return (1);
	else
		return (0);
}

static void	exit_message(t_shell *shell, int type, char *argument)
{
	if (type == 2)
	{
		write(2, "bash: exit: ", 12);
		if (ft_strlen(argument) > 0)
			write(2, argument, ft_strlen(argument));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	else
	{
		write(2, "bash: exit: too many arguments\n", 32);
		shell->exit = 1;
	}
}

void	ft_exit(t_shell *shell, t_cmd **cmd, int i)
{
	if (cmd[i]->args[1] != NULL)
	{
		if (compare_exit(cmd[i]->args[1]) || is_it_numeric(cmd[i]->args[1]))
			exit_message(shell, 2, cmd[i]->args[1]);
		if (cmd[i]->args[2] != NULL)
			exit_message(shell, 1, cmd[i]->args[1]);
		else
			exit(ft_atoi(cmd[i]->args[1]));
	}
	else
		exit(shell->exit);
}

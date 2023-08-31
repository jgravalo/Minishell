/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgravalo <jgravalo@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:37:09 by jgravalo          #+#    #+#             */
/*   Updated: 2023/08/31 15:08:21 by jgravalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_it_numeric(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_digit(line[i]) == 1)
			return (1);
		i++;
	}
	return (0);
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

void	exit_message(int type)
{
	write(2, "exit", 5);
	if (type == 2)
	{
		write(2, "\nbash: exit: numeric argument required\n", 39);
		exit(2);
	}
	else
	{
		write(2, "bash: exit: too many arguments\n", 32);
		exit(1);
	}
}

void	ft_exit(t_shell *shell, int n)
{
	int64_t		argument;
	uint64_t	u_argument;

	if (shell->struct_cmd[n]->args[1] != NULL)
	{
		argument = ft_atoi(shell->struct_cmd[n]->args[1]);
		if (shell->struct_cmd[n]->args[1][0] != '-')
		{
			u_argument = ft_u_atoi(shell->struct_cmd[n]->args[1]);
			if (u_argument > LONG_MAX
				|| is_it_numeric(shell->struct_cmd[n]->args[1]) == 0)
				exit_message(2);
			/*
				*probar todos los casos
			{
				write(2, "exit\n", 6);
				write(2, "bash: exit: numeric argument required\n", 39);
				exit(2);
			}
			*/
		}
		else
		{
			if (check_long_min(argument)
				|| is_it_numeric(shell->struct_cmd[n]->args[1]) == 0)
				exit_message(2);
			/*
			{
				write(2, "exit\n", 6);
				write(2, "bash: exit: numeric argument required\n", 39);
				exit(2);
			}
			*/
		}
		if (shell->struct_cmd[n]->args[2] != NULL)
			exit_message(1);
		/*
		{
			write(2, "exit", 5);
			write(2, "bash: exit: too many arguments\n", 32);
			exit(1);
		}
		*/
		exit(argument);
	}
	else
		exit(shell->exit);
}

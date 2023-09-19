/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:51:24 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/19 08:14:41 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

int	args_error(void)
{
	write(2, "bash: cd: too many arguments\n", 29);
	return (1);
}

int	is_dir_error(char *str, int exit)
{
	write(2, "bash: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": Is a directory\n", 17);
	return (exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:51:24 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/28 09:20:07 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

int	is_dir_error(char *str, int exit)
{
	write(2, "bash: ", 6);
	write(2, str, ft_strlen(str));
	write(2, ": Is a directory\n", 17);
	return (exit);
}

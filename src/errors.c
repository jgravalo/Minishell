/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/10 09:38:22 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

void	access_dir(void)
{
	ft_printf(2, "cd: error retrieving current directory: ");
	ft_printf(2, "getcwd: cannot access parent directories: ");
	ft_printf(2, "No such file or directory\n");
}

int	cmd_error(char *s, int n, int exit)
{
	ft_printf(2, "bash: %s: %s\n", s, strerror(n));
	return (exit);
}

int	dir_error(char *s, int n, int exit)
{
	ft_printf(2, "bash: cd: %s: %s\n", s, strerror(n));
	free(s);
	return (exit);
}

void	filedir_not_found(char *cmd)
{
	ft_printf(2, "bash: %s: No such file or directory\n", cmd);
	exit (127);
}

void	cmd_not_found(char *cmd)
{
	ft_printf(2, "%s: command not found\n", cmd);
	exit(127);
}

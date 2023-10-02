/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/10/02 15:28:13 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

void	access_dir(void)
{
	write(2, "cd: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories: ", 42);
	write(2, "No such file or directory\n", 26);
}

int	cmd_error(char *s, int n, int exit)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(s, ": ");
	str = ft_strjoin(tmp, strerror(n));
	write(2, "bash: ", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(tmp);
	free(str);
	return (exit);
}

int	dir_error(char *s, int n, int exit)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(s, ": ");
	str = ft_strjoin(tmp, strerror(n));
	write(2, "bash: cd: ", 10);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	free(tmp);
	free(str);
	free(s);
	return (exit);
}

void	filedir_not_found(char *cmd)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory", 27);
	write(2, "\n", 1);
	exit (127);
}

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

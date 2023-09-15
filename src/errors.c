/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/15 13:19:10 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
int	errors(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	i = 0;
	if (access(argv[argc - 1], F_OK) != -1
		&& access(argv[argc - 1], W_OK) == -1)
		exit(1);
	pipex->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (pipex->fdout == -1)
		exit(127);
	pipex->fdin = open(argv[1], O_RDONLY);
	return (i);
}
*/
int	cmd_error(char *s, int n, int exit)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(s, ": ");
	str = ft_strjoin(tmp, strerror(n));
	write(2, "bash: ", 7);
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
	return (exit);
}

void	filedir_not_found(char *cmd)
{
	write(2, "bash: ", 7);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory", 28);
	write(2, "\n", 1);
	exit (127);
}

void	cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

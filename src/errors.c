/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:56:43 by jgravalo          #+#    #+#             */
/*   Updated: 2023/08/15 13:35:08 by theonewhokn      ###   ########.fr       */
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

	str = ft_strjoin(s, ": ");
	str = ft_strjoin(str, strerror(n));
	write(2, "bash: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (exit);
}

int	file_error(char *s, int n)
{
	char	*str;

	str = ft_strjoin(s, ": ");
	str = ft_strjoin(str, strerror(n));
	write(2, "bash: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (0);
}
/*
void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->args[i])
	{
		free(pipex->args[i]);
		i++;
	}
	free(pipex->args);
	free(pipex->cmd);
}*/

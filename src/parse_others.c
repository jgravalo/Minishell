/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:35:05 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/13 17:42:50 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parse_ands(char *line, char **envp)
{
	char	**ands;
	int		i;
	int		exit;

	ands = ft_split(line, '&');
	i = 0;
	while (ands[i])
	{
		exit = parse_pipex(ands[i], envp);
		i++;
	}
	return (exit);
}

int	parse_ors(char *line, char **envp)
{
	char	**ors;
	int		i;
	int		exit;

	ors = ft_split(line, '|');
	i = 0;
	while (ors[i])
	{
		exit = parse_ands(ors[i], envp);
		if (exit == 0)
			break ;
		i++;
	}
	return (exit);
}

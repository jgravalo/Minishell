/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:08 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/07/13 18:00:11 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd(char **envp)
{
	char	*pwd;

	pwd = search_var("PWD", envp);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:08 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/17 19:25:20 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

int	pwd(char **envp)
{
	char	*pwd;
	char	buf[100];

	pwd = search_var_line("PWD", envp);
	if (pwd)
		;
	else
		pwd = getcwd(buf, 100);
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

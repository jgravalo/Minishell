/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:08 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/09 16:26:30 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../libft/libft.h"

int	pwd(t_shell *sh)
{
	char	*pwd;
	char	*buf;

	buf = NULL;
	printf("shpwd es %s\n", sh->pwd);
	pwd = getcwd(buf, 200);
	if (!pwd)
	{
		write(STDOUT_FILENO, sh->pwd, ft_strlen(sh->pwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		write(STDOUT_FILENO, pwd, ft_strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		free(pwd);
	}
	return (0);
}

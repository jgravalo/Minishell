/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:52 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/03 13:42:53 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell				sh;

	sh.line_number = 1;
	sh.exit = 0;
	if (alloc_envp(&sh, envp))
		return (1);
	if (!argc && !argv && !sh.envp)
		return (0);
	new_shell(&sh);
	free_m(sh.envp);
	return (sh.exit);
}

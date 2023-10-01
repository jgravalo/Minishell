/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:52 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/01 11:02:39 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell				sh;

	sh.line_number = 1;
	sh.exit = 0;
	alloc_envp(&sh, envp);
	if (!argc && !argv && !sh.envp)
		return (0);
	new_shell(&sh);
	free_m(sh.envp);
	return (sh.exit);
}

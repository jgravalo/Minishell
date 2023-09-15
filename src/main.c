/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:26:52 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 12:29:00 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell				sh;

	sh.line_number = 1;
	sh.exit = 0;
	alloc_envp(&sh, envp);
	if (!argc && !argv && !envp)
		return (0);
	new_shell(&sh);
	return (sh.exit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:11:04 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:19:02 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"

void	ft_unset(t_shell *sh, char *var)
{
	sh->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	check_malloc_error(sh->s_cmd);
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	check_malloc_error(sh->s_cmd[0]);
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	check_malloc_error(sh->s_cmd[0]->args);
	sh->s_cmd[0]->args[0] = ft_strdup("unset");
	check_malloc_error(sh->s_cmd[0]->args[0]);
	sh->s_cmd[0]->args[1] = ft_strdup(var);
	check_malloc_error(sh->s_cmd[0]->args[1]);
	sh->s_cmd[0]->args[2] = NULL;
	unset(sh, sh->s_cmd, 0);
	free_m(sh->s_cmd[0]->args);
	free(sh->s_cmd[0]);
	free(sh->s_cmd);
	sh->s_cmd = NULL;
}

void	ft_export(t_shell *sh, char *var)
{
	sh->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	check_malloc_error(sh->s_cmd);
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	check_malloc_error(sh->s_cmd[0]);
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	check_malloc_error(sh->s_cmd[0]->args);
	sh->s_cmd[0]->args[0] = ft_strdup("export");
	check_malloc_error(sh->s_cmd[0]->args[0]);
	sh->s_cmd[0]->args[1] = ft_strdup(var);
	check_malloc_error(sh->s_cmd[0]->args[1]);
	sh->s_cmd[0]->args[2] = NULL;
	export(sh, sh->s_cmd, 0);
	free_m(sh->s_cmd[0]->args);
	free(sh->s_cmd[0]);
	free(sh->s_cmd);
	sh->s_cmd = NULL;
}

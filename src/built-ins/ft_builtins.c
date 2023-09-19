/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:11:04 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/19 09:00:50 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"

void	ft_unset(t_shell *sh, char *var)
{
	sh->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("unset");
	sh->s_cmd[0]->args[1] = ft_strdup(var);
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
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("export");
	sh->s_cmd[0]->args[1] = ft_strdup(var);
	sh->s_cmd[0]->args[2] = NULL;
	export(sh, sh->s_cmd, 0);
	free_m(sh->s_cmd[0]->args);
	free(sh->s_cmd[0]);
	free(sh->s_cmd);
	sh->s_cmd = NULL;
}

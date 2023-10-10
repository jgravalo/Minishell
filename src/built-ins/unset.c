/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:00:23 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 09:59:16 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../../libft/libft.h"

static int	unset_n(char *var, t_shell *sh)
{
	char	**new;
	int		n;
	int		i;
	int		j;

	n = search_var_num(var, sh->envp);
	if (n < 0)
		return (0);
	new = (char **)malloc(sizeof(char *) * count_arr(sh->envp));
	check_malloc_error(new);
	i = 0;
	j = 0;
	while (sh->envp[i])
	{
		if (n == i && ++i)
			continue ;
		new[j++] = ft_strdup(sh->envp[i++]);
	}
	new[j] = NULL;
	if (ft_strcmp(var, "OLDPWD") == 0)
		sh->old_pwd = NULL;
	free_m(sh->envp);
	sh->envp = new;
	return (0);
}

int	unset(t_shell *sh, t_cmd **cmd, int i)
{
	int		j;

	j = 1;
	if (cmd[i]->args[j] == NULL)
		return (0);
	while (cmd[i]->args[j])
	{
		if (ft_strchr(cmd[i]->args[j], '=') != NULL)
		{
			ft_printf(2, "bash: unset: `%s\': ", cmd[i]->args[j]);
			ft_printf(2, "not a valid identifier\n");
			sh->exit++;
		}
		sh->exit += unset_n(cmd[i]->args[j], sh);
		j++;
	}
	return (sh->exit);
}

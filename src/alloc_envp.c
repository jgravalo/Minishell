/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:27:15 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/18 12:02:48 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/builtins.h"

static void	over_999_shlvl(t_shell *sh, int shlvl, char *tmp)
{
	tmp = ft_itoa(shlvl + 1);
	write(2, "bash: warning: shell level (", 28);
	write(2, tmp, ft_strlen(tmp));
	write(2, ") too high, resetting to 1\n", 27);
	change_var(sh, "SHLVL", tmp);
}

static void	get_shlvl(t_shell *sh)
{
	int		shlvl;

	if (getenv("SHLVL") != NULL)
	{
		shlvl = ft_atoi(getenv("SHLVL"));
		if (shlvl < 0)
		{
			sh->tmp = ft_itoa(0);
			change_var(sh, "SHLVL", sh->tmp);
		}
		else if (shlvl > 999)
			over_999_shlvl(sh, shlvl, sh->tmp);
		else
		{
			sh->tmp = ft_itoa(shlvl + 1);
			change_var(sh, "SHLVL", sh->tmp);
		}
	}
	else
	{
		ft_export(sh, "SHLVL");
		sh->tmp = ft_itoa(1);
		change_var(sh, "SHLVL", sh->tmp);
	}
	free(sh->tmp);
}

int	change_var(t_shell *sh, char *var, char *content)
{
	int		var_num;
	char	*tmp;

	var_num = search_var_num(var, sh->envp);
	if (var_num < 0)
		return (1);
	tmp = ft_strjoin(var, "=");
	free(sh->envp[var_num]);
	sh->envp[var_num] = ft_strjoin(tmp, content);
	if (ft_strlen(content) == 0)
		sh->envp[var_num] = ft_strdup(sh->envp[var_num]);
	free(tmp);
	return (0);
}

void	alloc_envp(t_shell *sh, char **envp)
{
	int		i;
	char	buffer[100];

	sh->envp = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	i = 0;
	while (envp[i])
	{
		sh->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	sh->envp[i] = NULL;
	if (getenv("SHELL") != NULL)
		change_var(sh, "SHELL", getcwd(buffer, 100));
	get_shlvl(sh);
}


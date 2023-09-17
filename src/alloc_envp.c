/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:27:15 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/17 19:06:37 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/builtins.h"

void	empty_old_pwd(t_shell *sh)
{
	sh->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("unset");
	sh->s_cmd[0]->args[1] = ft_strdup("OLDPWD");
	sh->s_cmd[0]->args[2] = NULL;
	unset(sh, sh->s_cmd, 0);
	free_m(sh->s_cmd[0]->args);
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("export");
	sh->s_cmd[0]->args[1] = ft_strdup("OLDPWD");
	sh->s_cmd[0]->args[2] = NULL;
	export(sh, sh->s_cmd, 0);
	free_m(sh->s_cmd[0]->args);
	free(sh->s_cmd[0]);
	free(sh->s_cmd);
	sh->old_pwd = ft_strdup("");
}

static void	export_shlvl(t_shell *sh)
{
	sh->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("export");
	sh->s_cmd[0]->args[1] = ft_strdup("SHLVL");
	sh->s_cmd[0]->args[2] = NULL;
	export(sh, sh->s_cmd, 0);
	free_m(sh->s_cmd[0]->args);
	free(sh->s_cmd[0]);
	free(sh->s_cmd);
}

static void	get_shlvl(t_shell *sh)
{
	int	shlvl;

	if (getenv("SHLVL") != NULL)
	{
		shlvl = ft_atoi(getenv("SHLVL"));
		if (shlvl < 0)
			change_var(sh, "SHLVL", ft_itoa(0));
		else if (shlvl > 999)
		{
			write(2, "bash: warning: shell level (", 28);
			write(2, ft_itoa(shlvl + 1), ft_strlen(ft_itoa(shlvl + 1)));
			write(2, ") too high, resetting to 1\n", 27);
			change_var(sh, "SHLVL", ft_itoa(1));
		}
		else
			change_var(sh, "SHLVL", ft_itoa(shlvl + 1));
	}
	else
	{
		export_shlvl(sh);
		change_var(sh, "SHLVL", ft_itoa(1));
	}
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
	empty_old_pwd(sh);
	if (getenv("SHELL") != NULL)
		change_var(sh, "SHELL", getcwd(buffer, 100));
	get_shlvl(sh);
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

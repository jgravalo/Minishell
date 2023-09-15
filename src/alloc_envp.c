/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:27:15 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 13:12:16 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	empty_old_pwd(t_shell *sh)
{
	int	i;

	i = 0;
	sh->s_cmd = (t_cmd **)malloc(sizeof (t_cmd *));
	sh->s_cmd[0] = (t_cmd *)malloc(sizeof (t_cmd));
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("unset");
	sh->s_cmd[0]->args[1] = ft_strdup("OLDPWD");
	sh->s_cmd[0]->args[2] = NULL;
	unset(sh, sh->s_cmd, &i);
	free_m(sh->s_cmd[0]->args);
	sh->s_cmd[0]->args = (char **)malloc(sizeof (char *) * 3);
	sh->s_cmd[0]->args[0] = ft_strdup("export");
	sh->s_cmd[0]->args[1] = ft_strdup("OLDPWD");
	sh->s_cmd[0]->args[2] = NULL;
	export(sh, sh->s_cmd, &i);
	free_m(sh->s_cmd[0]->args);
	free(sh->s_cmd[0]);
	free(sh->s_cmd);
	sh->old_pwd = ft_strdup("");
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
	if (getenv("SHLVL") != NULL)
		change_var(sh, "SHLVL", ft_itoa(ft_atoi(getenv("SHLVL")) + 1));
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

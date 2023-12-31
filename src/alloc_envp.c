/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:27:15 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/10 11:58:20 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../inc/builtins.h"
#include "../libft/libft.h"

static void	over_999_shlvl(t_shell *sh, int shlvl, char *tmp)
{
	ft_printf(2, "bash: warning: ");
	ft_printf(2, "shell level (%d) too high, resetting to 1\n", shlvl + 1);
	tmp = ft_itoa(1);
	change_var(sh, "SHLVL", tmp);
}

static void	get_shlvl(t_shell *sh)
{
	sh->tmp = NULL;
	if (getenv("SHLVL") != NULL)
	{
		sh->shlvl = ft_atoi(getenv("SHLVL"));
		if (sh->shlvl < 0)
		{
			sh->tmp = ft_itoa(0);
			change_var(sh, "SHLVL", sh->tmp);
		}
		else if (sh->shlvl > 999)
			over_999_shlvl(sh, sh->shlvl, sh->tmp);
		else
		{
			sh->tmp = ft_itoa(sh->shlvl + 1);
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
	if (var_num < 0 || !var || !content)
		return (1);
	tmp = ft_strjoin(var, "=");
	free(sh->envp[var_num]);
	sh->envp[var_num] = ft_strjoin(tmp, content);
	if (ft_strlen(content) == 0)
		sh->envp[var_num] = ft_strdup(sh->envp[var_num]);
	free(tmp);
	return (0);
}

int	alloc_envp(t_shell *sh, char **envp)
{
	int		i;
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	sh->envp = (char **)malloc(sizeof (char *) * (count_arr(envp) + 1));
	check_malloc_error(sh->envp);
	i = 0;
	while (envp[i])
	{
		sh->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	sh->envp[i] = NULL;
	if (getenv("SHELL") != NULL)
	{
		tmp = getcwd(buffer, 200);
		change_var(sh, "SHELL", tmp);
		free(tmp);
	}
	get_shlvl(sh);
	ft_unset(sh, "OLDPWD");
	sh->pwd = getcwd(buffer, 200);
	return (0);
}

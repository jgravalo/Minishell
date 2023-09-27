/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:13:28 by jgravalo          #+#    #+#             */
/*   Updated: 2023/09/27 20:12:10 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../../libft/libft.h"

static int	parse_var(char *var)
{
	int	i;

	i = 0;
	if (is_digit(var[i]) == 1 || is_alpha(var[i]) == 0)
		return (1);
	i++;
	while (var[i])
	{
		if (var[i] == '+' && var[i + 1] == '=')
			return (2);
		if (var[i] == '=')
			return (0);
		if (is_alpha_num(var[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	replace_existing(char *line, t_shell *sh)
{
	char	**new;
	int		i;
	char	*var;

	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	var = ft_substr(line, 0, i);
	i = 0;
	new = (char **)malloc(sizeof(char *) * (count_arr(sh->envp) + 1));
	if (!new)
		return (1);
	while (sh->envp[i] != NULL)
	{
		if (ft_varcmp(var, sh->envp[i], ft_strlen(var)) == 0)
			new[i] = ft_strdup(line);
		else
			new[i] = ft_strdup(sh->envp[i]);
		i++;
	}
	new[i] = NULL;
	free(sh->envp);
	sh->envp = new;
	return (0);
}

static int	cat_existing(char *line, t_shell *sh)
{
	char	*tmp;
	int		i;
	char	*var;

	i = 0;
	while (line[i] != '+' && line[i] != '=' && line[i] != '\0')
		i++;
	var = ft_substr(line, 0, i);
	i = 0;
	while (sh->envp[i] != NULL)
	{
		if (ft_varcmp(var, sh->envp[i], ft_strlen(var)) == 0)
		{
			tmp = ft_strjoin(ft_strchr(sh->envp[i], '='),
					ft_strchr(line, '=') + 1);
			sh->envp[i] = ft_strjoin(var, tmp);
			break ;
		}
		i++;
	}
	return (0);
}

static int	add_envp(char *var, t_shell *sh, int type)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (count_arr(sh->envp) + 2));
	if (!new)
		return (1);
	i = 0;
	while (sh->envp[i] != NULL)
	{
		new[i] = ft_strdup(sh->envp[i]);
		i++;
	}
	if (type == 2)
		new[i++] = add_without_plus(var);
	else
		new[i++] = ft_strdup(var);
	new[i] = NULL;
	free_m(sh->envp);
	sh->envp = new;
	return (0);
}

int	export_n(char *var, t_shell *sh)
{
	int		type;

	type = parse_var(var);
	if (type == 1)
		return (write_not_valid(var));
	if (is_existing(var, sh->envp) == 1)
		return (0);
	else if (is_existing(var, sh->envp) == 2 && type == 0)
		return (replace_existing(var, sh));
	else if (is_existing(var, sh->envp) == 2 && type == 2)
		return (cat_existing(var, sh));
	else
		return (add_envp(var, sh, type));
}

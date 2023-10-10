/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:52:19 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/10/10 09:58:07 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/builtins.h"
#include "../../libft/libft.h"

char	*add_without_plus(char *var)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof (char) * ft_strlen(var));
	check_malloc_error(new);
	while (var[i])
	{
		if (var[i] != '+')
			new[j++] = var[i++];
		else
			i++;
	}
	new[j] = '\0';
	return (new);
}

static char	*for_equal(char *var)
{
	char	*new;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	j = 0;
	i = 0;
	new = malloc(sizeof (char) * (ft_strlen(var) + 3));
	check_malloc_error(new);
	while (var[j])
	{
		if (flag == 0 && var[j] == '=')
		{
			new[i++] = var[j++];
			new[i++] = '\"';
			flag = 1;
		}
		else
			new[i++] = var[j++];
	}
	new[i++] = '\"';
	new[i] = '\0';
	return (new);
}

static char	*put_var(char *var)
{
	char	*new;

	if (ft_strchr(var, '=') != NULL)
	{
		new = for_equal(var);
		return (new);
	}
	return (NULL);
}

void	write_var(char *var, char **envp, int i)
{
	var = put_var(envp[i]);
	ft_printf(1, "declare -x ");
	if (!var)
		ft_printf(1, "%s", envp[i]);
	else
	{
		ft_printf(1, "%s", var);
		free(var);
	}
	ft_printf(1, "\n");
}

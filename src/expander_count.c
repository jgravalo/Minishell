/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:23:42 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/10/04 10:49:44 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"
#include "../libft/libft.h"

char	*get_var(char *str, int *i)
{
	int	j;
	int	start;

	j = 0;
	(*i)++;
	start = *i;
	while (str[*i] && is_alpha_num(str[*i]) && str[*i] != ' '
		&& str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
	{
		(*i)++;
		j++;
	}
	return (ft_substr(str, start, j));
}

static int	check_single(char *str, int *count, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		(*count)++;
		while (str[*i] != '\'')
		{
			(*i)++;
			(*count)++;
		}
		(*i)++;
		(*count)++;
		return (1);
	}
	return (0);
}

static int	check_double(char *str, int *count, int *i, char **envp)
{
	char	*var;

	if (str[*i] == '\"')
	{
		(*i)++;
		(*count)++;
		while (str[*i] != '\"')
		{
			if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
			{
				var = get_var(str, i);
				if (ft_strcmp(var, "?") == 0)
					(*count)++;
				else
					(*count) += ft_strlen(search_var_line(var, envp));
				free(var);
			}
			else
				move_ptrs(i, count);
		}
		(*i)++;
		(*count)++;
		return (1);
	}
	return (0);
}

static int	check_normal(char *str, int *count, int *i, char **envp)
{
	char	*var;

	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{
		if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
		{
			var = get_var(str, i);
			if (ft_strcmp(var, "?") == 0)
				(*count)++;
			else
				(*count) += ft_strlen(search_var_line(var, envp));
			if (var)
				free(var);
		}
		else if (str[*i] == '$' && (str[*i + 1] == '\''
				|| str[*i + 1] == '\"'))
			(*i)++;
		else
		{
			(*i)++;
			(*count)++;
		}
	}
	return (1);
}

int	count_expstr(t_shell *sh, char *str, int *i)
{
	int	count;

	sh->var_cat = 0;
	sh->var_quoted = 0;
	count = 0;
	while (str[*i])
	{
		check_single(str, &count, i);
		check_double(str, &count, i, sh->envp);
		check_normal(str, &count, i, sh->envp);
	}
	return (count);
}

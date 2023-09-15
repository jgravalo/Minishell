/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:36:44 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/15 15:08:43 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_var(char *str, int *i)
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

static void	check_single(char *str, int *i, int *j, t_shell *shell)
{
	int	start;
	int	end;

	if (str[*j] == '\'')
	{
		start = *i;
		shell->tmp[(*i)++] = str[(*j)++];
		while (str[*j] != '\'')
			shell->tmp[(*i)++] = str[(*j)++];
		shell->tmp[(*i)++] = str[(*j)++];
		end = *i - 1;
		quoteback(&shell->quote, quotenew(start, end));
	}
}

static int	check_double(char *str, int *i, int *j, t_shell *shell)
{
	char	*var;
	char	*exp;
	int		start;
	int		end;
	int		m;

	if (str[*j] == '\"')
	{
		start = *i;
		shell->tmp[(*i)++] = str[(*j)++];
		while (str[*j] != '\"')
		{
			m = 0;
			if (str[*j] == '$' && is_alpha_num_exp(str[(*j) + 1]) == 1)
			{
				var = get_var(str, j);
				if (ft_strcmp(var, "?") == 0)
					exp = ft_itoa(shell->exit);
				else
					exp = ft_strdup(search_var_line(var, shell->envp));
				while (exp && exp[m])
					shell->tmp[(*i)++] = exp[m++];
			}
			else
				shell->tmp[(*i)++] = str[(*j)++];
		}
		shell->tmp[(*i)++] = str[(*j)++];
		end = *i - 1;
		quoteback(&shell->quote, quotenew(start, end));
	}
}

static void	check_normal(char *str, int *i, int *j, t_shell *shell)
{
	char	*var;
	char	*exp;
	int		m;

	while (str[*j] && str[*j] != '\'' && str[*j] != '\"')
	{
		m = 0;
		if (str[*j] == '$' && is_alpha_num_exp(str[*j + 1]) == 1)
		{
			var = get_var(str, j);
			if (ft_strcmp(var, "?") == 0)
				exp = ft_itoa(shell->exit);
			else
				exp = ft_strdup(search_var_line(var, shell->envp));
			while (exp && exp[m])
				shell->tmp[(*i)++] = exp[m++];
		}
		else if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
			(*j)++;
		else
			shell->tmp[(*i)++] = str[(*j)++];
	}
}
/* 
static void	expand(t_shell *shell, char *str, int *j)
{
	int	i;

	i = 0;
	while (str[*j])
	{
		check_single(str, &i, j, shell);
		check_double(str, &i, j, shell);
		check_normal(str, &i, j, shell);
	}
	shell->tmp[i] = '\0';
} */

char	*expand_str(t_shell *shell, t_arg *arg, int *i, int *j)
{
	int	len;
	int	n;

	n = 0;
	len = count_expstr(shell, arg->arg, i);
	if (len > 0)
	{
		shell->tmp = malloc(sizeof (char) * len + 1);
		while (arg->arg[*j])
		{
			check_single(arg->arg, &n, j, shell);
			check_double(arg->arg, &n, j, shell);
			check_normal(arg->arg, &n, j, shell);
		}
		shell->tmp[n] = '\0';
	}
	else
		shell->tmp = NULL;
	return (shell->tmp);
}

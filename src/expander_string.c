/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theonewhoknew <theonewhoknew@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:36:44 by theonewhokn       #+#    #+#             */
/*   Updated: 2023/09/16 10:21:31 by theonewhokn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/utils.h"

static void	check_single(char *str, int *i, int *j, t_shell *sh)
{
	int	start;
	int	end;

	if (str[*j] == '\'')
	{
		start = *i;
		sh->tmp[(*i)++] = str[(*j)++];
		while (str[*j] != '\'')
			sh->tmp[(*i)++] = str[(*j)++];
		sh->tmp[(*i)++] = str[(*j)++];
		end = *i - 1;
		quoteback(&sh->quote, quotenew(start, end));
	}
}

static void	double_aux(char *str, int *i, int *j, t_shell *sh)
{
	char	*var;
	char	*exp;
	int		m;

	m = 0;
	var = get_var(str, j);
	if (ft_strcmp(var, "?") == 0)
		exp = ft_itoa(sh->exit);
	else
		exp = ft_strdup(search_var_line(var, sh->envp));
	while (exp && exp[m])
		sh->tmp[(*i)++] = exp[m++];
	if (exp)
		free(exp);
}

static void	check_double(char *str, int *i, int *j, t_shell *sh)
{
	int		start;
	int		end;

	if (str[*j] == '\"')
	{
		start = *i;
		sh->tmp[(*i)++] = str[(*j)++];
		while (str[*j] != '\"')
		{
			if (str[*j] == '$' && is_alpha_num_exp(str[(*j) + 1]) == 1)
				double_aux(str, i, j, sh);
			else
				sh->tmp[(*i)++] = str[(*j)++];
		}
		sh->tmp[(*i)++] = str[(*j)++];
		end = *i - 1;
		quoteback(&sh->quote, quotenew(start, end));
	}
}

static void	check_normal(char *str, int *i, int *j, t_shell *sh)
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
				exp = ft_itoa(sh->exit);
			else
				exp = ft_strdup(search_var_line(var, sh->envp));
			while (exp && exp[m])
				sh->tmp[(*i)++] = exp[m++];
		}
		else if (str[*i] == '$' && (str[*i + 1] == '\'' || str[*i + 1] == '\"'))
			(*j)++;
		else
			sh->tmp[(*i)++] = str[(*j)++];
	}
}

char	*expand_str(t_shell *sh, t_arg *arg, int *i, int *j)
{
	int	len;
	int	n;

	n = 0;
	len = count_expstr(sh, arg->arg, i);
	if (len > 0)
	{
		sh->tmp = malloc(sizeof (char) * len + 1);
		while (arg->arg[*j])
		{
			check_single(arg->arg, &n, j, sh);
			check_double(arg->arg, &n, j, sh);
			check_normal(arg->arg, &n, j, sh);
		}
		sh->tmp[n] = '\0';
	}
	else
		sh->tmp = NULL;
	return (sh->tmp);
}

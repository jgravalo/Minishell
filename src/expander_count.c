#include  "../inc/minishell.h"

static char *get_var(char *str, int *i)
{
	int j;
	int start;

	j = 0;
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
	{	
		(*i)++;
		j++;
	}
	return (ft_substr(str, start, j));
}

static int check_single(char *str, int *count, int *i)
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

static int check_double(char *str, int *count, int *i, char **envp)
{	
	char *var;

	if (str[*i] == '\"')
	{	
		(*i)++;
		(*count)++;
		while (str[*i] != '\"')
		{
			if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
			{	
				var	=	get_var(str, i);
				if (ft_strcmp(var, "?") == 0)
					(*count)++;
				else
					(*count) +=	ft_strlen(search_var_line(var, envp));
				(*i)++;
				(*count)++;
				return (1);
			}
			else
			{	
				(*i)++;
				(*count)++;
			}
		}
		(*i)++;
		(*count)++;
		return (0);
	}
	return (0);
}

static int check_normal(char *str, int *count, int *i, char **envp)
{	
	char *var;

	while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
	{	
		if (str[*i] == '$' && is_alpha_num_exp(str[*i + 1]) == 1)
		{	
			var	=	get_var(str, i);
			if (ft_strcmp(var, "?") == 0)
				(*count)++;
			else
				(*count) +=	ft_strlen(search_var_line(var, envp));
			return (1);
		}
		else
		{	
			(*i)++;
			(*count)++;
		}
	}
	return (0);
}

int count_expstr(t_shell *shell, char *str, int *i)
{
	int count;
	shell->var_cat = 0;
	shell->var_quoted = 0;

	count = 0;
	while (str[*i])
	{	
		check_single(str, &count, i);
		if (check_double(str, &count, i, shell->envp))
		{
			shell->var_quoted = 1;
			if (str[*i + 1] != ' ')
				shell->var_cat = 1;
			return (count);
		}
		if (check_normal(str, &count, i, shell->envp))
		{	
			if (str[*i + 1] == ' ')
				shell->var_cat = 1;
			return (count);
		}
	}
	return (count);
}
